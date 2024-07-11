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
vec2 cb_depthBufferSize = textureSize(gDepth,0);

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


float linearizeDepth(float depth){
    return (2.0 * cb_nearPlaneZ * cb_farPlaneZ) / (cb_farPlaneZ + cb_nearPlaneZ - depth * (cb_farPlaneZ - cb_nearPlaneZ));

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

mat4 createPixelTransformMatrix(vec2 viewportDimensions) {

    mat4 projectToPixelMatrix = mat4(
        vec4(viewportDimensions.x / 2.0, 0.0, 0.0, 0.0),
        vec4(0.0, viewportDimensions.y / 2.0, 0.0, 0.0),
        vec4(0.0, 0.0, 1.0, 0.0),
        vec4(viewportDimensions.x / 2.0, viewportDimensions.y / 2.0, 0.0, 1.0)
    );
    return projectToPixelMatrix;
}

float linearDepthTexelFetch(vec2 hitPixel){
    return linearizeDepth(texture(gDepth, hitPixel).r);
}

bool traceScreenSpaceRay(
    vec3 csOrigin,
    vec3 csDir,
    float jitter,
out vec2 hitPixel,
out vec3 hitPoint) {

    float rayLength = ((csOrigin.z + csDir.z * cb_maxDistance) > cb_nearPlaneZ) ?
    (cb_nearPlaneZ - csOrigin.z) / csDir.z : cb_maxDistance;
    vec3 csEndPoint = csDir * rayLength + csOrigin;

    hitPixel = vec2(-1, -1);

    // Transform to screen space
    mat4 projectToPixelMaterix = createPixelTransformMatrix(cb_depthBufferSize);

    vec4 H0 = projectToPixelMaterix * vec4(csOrigin, 1.0);
    vec4 H1 = projectToPixelMaterix * vec4(csEndPoint, 1.0);

    float k0 = 1.0 / H0.w;
    float k1 = 1.0 / H1.w;

    vec3 Q0 = csOrigin * k0;
    vec3 Q1 = csEndPoint * k1;

    vec2 P0 = H0.xy * k0;
    vec2 P1 = H1.xy * k1;

    hitPixel = vec2(-1.0, -1.0);

    P1 += vec2((distanceSquared(P0, P1) < 0.0001) ? 0.01 : 0.0);
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

    float strideScale = 1.0 - min(1.0, csOrigin.z * cb_strideZCutoff);
    float stride = 1.0 + strideScale * cb_stride;

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
    float sceneZmax = rayZmax + 100.0;

    float end = P1.x * stepDir;

    vec2 P = P0;
    float stepCount = 0.0;

    while (((P.x * stepDir) <= end) &&
    (stepCount < cb_maxSteps) &&
    ((rayZmax < sceneZmax - cb_zThickness) || (rayZmin > sceneZmax)) &&
    (sceneZmax != 0.0)) {

        P += dP;
        stepCount++;

        Q.z += dQ.z;
        K += dk;

        hitPixel = permute ? P.yx : P.yx;

        rayZmin = prevZMaxEstimate;
        rayZmax = (dQ.z * 0.5 + Q.z) / (dk * 0.5 + K);
        prevZMaxEstimate = rayZmax;
        if (rayZmin > rayZmax) {
            swap(rayZmin, rayZmax);
        }

        sceneZmax = texture(gDepth, hitPixel).r;
    }

    Q.xy += dQ.xy * stepCount;
    hitPoint = Q * (1.0 / K);

    return intersetcsDepthBuffer(sceneZmax, rayZmin, rayZmax);
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
    vec3 normalVS = texture(gNormal, TexCoords).xyz;
    normalVS = normalize(vec3(vec4(normalVS,1.0)*View));

    float depth = texture(gDepth, TexCoords).r;

    vec3 rayOriginVS = vec3(vec4(PositionFromDepth(depth),1.0)*invProjection);

    vec3 toPostionVS = normalize(rayOriginVS);
    vec3 rayDirectionVS =reflect(normalize(toPostionVS), normalize(normalVS));

    rayDirectionVS = vec3(vec4(rayDirectionVS, 1.0)* View);

    vec2 hitPixel = vec2(0.0);
    vec3 hitPoint = vec3(0.0);

    bool intersection = traceScreenSpaceRay(rayOriginVS, rayDirectionVS, 0.2,
                                            hitPixel, hitPoint);
    vec3 col;
    col = texture(gColourShininess, hitPixel.xy).rgb;
    FragColor = vec4(col,1.0);
}