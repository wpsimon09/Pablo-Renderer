#version 460

uniform sampler2D gNormal;
uniform sampler2D gPosition;
uniform sampler2D gColourShininess;
uniform sampler2D gRenderedScene;
uniform sampler2D gDepth;

uniform mat4 Projection;
uniform mat4 invProjection;

uniform mat4 View;
uniform mat4 invView;

in vec2 TexCoords;

out vec4 FragColor;

// dimensions of the z-buffer

// thickness to ascribe to each pixel in the depth buffer
uniform float cb_zThickness;

// the camera's near z plane
uniform float cb_nearPlaneZ;

uniform float cb_farPlaneZ ;

// Step in horizontal or vertical pixels between samples. This is a float
// because integer math is slow on GPUs, but should be set to an integer >= 1.
uniform float cb_stride;

// Maximum number of iterations. Higher gives better images but may be slow.
uniform float cb_maxSteps;
// Maximum camera-space distance to trace before returning a miss.
uniform float cb_maxDistance;

// More distant pixels are smaller in screen space. This
//value tells at what point to
// start relaxing the stride to give higher quality reflections for objects far from
// the camera.
uniform float cb_strideZCutoff;

// the number of mip levels in the convolved color buffer
float cb_numMips = 0;

// determines where to start screen edge fading of effect
uniform float cb_fadeStart ;

// determines where to end screen edge fading of effect
uniform float cb_fadeEnd ;

// padding for alignment
uniform float cb_sslr_padding0 ;

mat4 projectionToPixelSpaceMatrix(){
    mat4 ndcToTextureSpace = mat4(
        0.5, 0.0, 0.0, 0.0,       // Scale x by 0.5
        0.0, 0.5, 0.0, 0.0,       // Scale y by 0.5
        0.0, 0.0, 1.0, 0.0,       // Keep z
        0.5, 0.5, 0.0, 1.0        // Translate x and y by 0.5
    );

    return ndcToTextureSpace * Projection;
}

float distanceSquared(vec2 a, vec2 b){
    a -= b;
    return dot(a,a);
}

bool intersetcsDepthBuffer(float z, float minZ, float maxZ){
    float depthScale = min(1.0f, z* cb_strideZCutoff);
    z += cb_zThickness + mix(0.0f, 2.0f, depthScale);
    return (maxZ >= z) && (minZ - cb_zThickness <=z);
}

void swap(inout float a, inout float b){
    float t = a;
    a = b;
    b = t;
}


bool traceScreenSpaceRay(
    vec3 csOrigin,
    vec3 csDir,
    float jitter,
    vec2 depthBufferSize,
out vec2 hitPixel,
out vec3 hitPoint) {

    float rayLength = ((csOrigin.z + csDir.z * cb_maxDistance) > cb_nearPlaneZ) ?
    (cb_nearPlaneZ - csOrigin.z) / csDir.z : cb_maxDistance;
    vec3 csEndPoint = csDir * rayLength + csOrigin;

    hitPixel = vec2(-1, -1);

    //from NDC to pixel space
    mat4 projectToPixelMatrix = projectionToPixelSpaceMatrix();
    vec4 H0 =  projectToPixelMatrix * vec4(csOrigin,   1.0);

    vec4 H1 = projectToPixelMatrix * vec4(csEndPoint, 1.0);

    //from perspective devision
    float k0 = 1.0f / H0.w;
    float k1 = 1.0f / H1.w;

    vec3 Q0 = csOrigin * k0;
    vec3 Q1 = csEndPoint * k1;

    vec2 P0 = H0.xy * k0;
    vec2 P1 = H1.xy * k1;

    hitPixel = vec2(-1.0, -1.0);

    P1 += vec2((distanceSquared(P0, P1) < 0.0001) ? vec2(0.01,0.01) : vec2(0.0,0.0));
    vec2 delta = P1 - P0;

    bool permute = false;
    if (abs(delta.x) < abs(delta.y)) {
        permute = true;
        delta = delta.yx;
        P1 = P1.yx;
        P0 = P0.yx;
    }

    float stepDir = sign(delta.x);
    float invdx = stepDir / delta.x;
    vec2 dP = vec2(stepDir, invdx * delta.y);

    vec3 dQ = (Q1 - Q0) * invdx;
    float dk = (k1 - k0) * invdx;

    float strideScale = 1.0f - min(1.0, csOrigin.z * cb_strideZCutoff);
    float stride = 1.0f + strideScale * cb_stride;

    dP *= stride;
    dQ *= stride;
    dk *= stride;
    P0 += dP * jitter;
    Q0 += dQ * jitter;
    k0 += dk * jitter;

    vec3 Q = Q0;
    float K = k0;

    float prevZMaxEstimate = csOrigin.z;
    float rayZmin = prevZMaxEstimate;
    float rayZmax = prevZMaxEstimate;
    float sceneZmax = rayZmax + 1e4;

    float end = P1.x * stepDir;

    vec2 P = P0;
    float stepCount = 0.0;

    while (((P.x * stepDir) <= end) &&
    (stepCount < cb_maxSteps) &&
    ((rayZmax < sceneZmax - cb_zThickness) || (rayZmin > sceneZmax)) && (sceneZmax != 0.0))
    {
        hitPixel = permute ? P.yx : P;
        rayZmin = prevZMaxEstimate;
        rayZmax = (dQ.z * 0.5 + Q.z) / (dk * 0.5 + K);
        prevZMaxEstimate = rayZmax;

        if (rayZmin > rayZmax) {
            swap(rayZmin, rayZmax);
        }

        sceneZmax = texelFetch(gDepth, ivec2(hitPixel), 0).r;

        P += dP;
        Q.z += dQ.z;
        K += dk;
        stepCount += 1.0;
    }



    Q.xy += dQ.xy * stepCount;
    hitPoint = Q * (1.0 / K);

    return (rayZmax >= sceneZmax - cb_zThickness) && (rayZmin <= sceneZmax);
}


vec3 PositionFromDepth(float depth) {
    float z = depth * 2.0 - 1.0;

    vec4 clipSpacePosition = vec4(TexCoords * 2.0 - 1.0, z, 1.0);
    vec4 viewSpacePosition = invProjection * clipSpacePosition;

    // Perspective division
    viewSpacePosition.xyz /= viewSpacePosition.w;

    return viewSpacePosition.xyz;
}



void main() {
    vec2 cb_depthBufferSize = textureSize(gDepth,0);


    vec3 normalWorldSpace = normalize(texture(gNormal, TexCoords).xyz);
    vec3 normalViewSpace = normalize(vec3(View * vec4(normalWorldSpace, 0.0)));

    vec3 normalVS =  normalViewSpace;

    vec3 PositionWS = texture(gPosition, TexCoords).xyz;
    vec3 positionVS = normalize(vec3(View * vec4(PositionWS,1.0)));

    float depth = texture(gDepth, TexCoords).r;

    vec3 rayOriginVS =PositionFromDepth(depth) ;

    vec3 toPostionVS = normalize(rayOriginVS);
    vec3 rayDirectionVS = normalize(reflect(toPostionVS, normalVS));

    vec2 hitPixel = vec2(0.0);
    vec3 hitPoint = vec3(0.0);

    bool intersection = traceScreenSpaceRay(rayOriginVS, rayDirectionVS, 0.2, cb_depthBufferSize,
                                            hitPixel, hitPoint);
    vec3 col = vec3(0.0);


    if(intersection)
        col = texture(gColourShininess, vec2(hitPixel.x, hitPixel.y)).rgb;
    else
        col = vec3(0.0);
    FragColor = vec4(col,1.0);
}