#version 460

const float INF = 1.0 / 0.0;
const float NEG_INF = -1.0 / 0.0;

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

uniform float cb_farPlaneZ;

// Step in horizontal or vertical pixels between samples. This is a float
// because integer math is slow on GPUs, but should be set to an integer >= 1.
uniform float cb_stride;

uniform vec2 viewPortSize;

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
uniform float cb_fadeStart;

// determines where to end screen edge fading of effect
uniform float cb_fadeEnd;

// padding for alignment
uniform float cb_sslr_padding0;

mat4 projectionToPixelSpaceMatrix() {
    mat4 ndcToTextureSpace = mat4(
        0.5, 0.0, 0.0, 0.0,
        0.0, 0.5, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.5, 0.5, 0.0, 1.0
    );

    return ndcToTextureSpace * Projection;
}

float distanceSquared(vec2 a, vec2 b) {
    a -= b;
    return dot(a, a);
}

void swap(inout float a, inout float b) {
    float t = a;
    a = b;
    b = t;
}

vec3 computeClipInfo(float zn, float zf) {
    if (zf == NEG_INF) {
        return vec3(zn, -1.0f, + 1.0f);
    } else {
        return vec3(zn * zf, zn - zf, zf);
    }
}

float reconstructCSZ(float depthBufferValue, vec3 clipInfo) {
    return clipInfo[0] / (depthBufferValue * clipInfo[1] + clipInfo[2]);
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

    vec4 H0 = projectToPixelMatrix * vec4(csOrigin, 1.0);
    vec4 H1 = projectToPixelMatrix * vec4(csEndPoint, 1.0);
    //perspective devision made faster
    float k0 = 1.0f / H0.w;
    float k1 = 1.0f / H1.w;

    vec3 Q0 = csOrigin * k0;
    vec3 Q1 = csEndPoint * k1;

    // screen space end points
    vec2 P0 = H0.xy * k0;
    vec2 P1 = H1.xy * k1;

    hitPixel = vec2(-1.0, -1.0);

    P1 += vec2((distanceSquared(P0, P1) < 0.0001) ? vec2(0.01, 0.01) : vec2(0.0, 0.0));
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

    for (vec2 P = P0;
        ((P.x * stepDir) <= end) &&
        (stepCount < cb_maxSteps) &&
        ((rayZmax < sceneZmax - cb_zThickness) || (rayZmax > sceneZmax)) && (sceneZmax != 0.0);
        P += dP)
    {

        Q.z += dQ.z;
        K += dk;
        stepCount += 1.0;
        hitPixel = permute ? P.yx : P;

        rayZmin = prevZMaxEstimate;

        // Compute the value at 1/2 pixel into the future
        rayZmax = (dQ.z * 0.5 + Q.z) / (dk * 0.5 + K);
        prevZMaxEstimate = rayZmin;
        if (rayZmin > rayZmax) {
            swap(rayZmin, rayZmax);
        }

        sceneZmax = texelFetch(gDepth, ivec2(hitPixel), 0).r;
    }
    Q.xy += dQ.xy * stepCount;
    hitPoint = Q * (1.0 / K);
    hitPoint.y = depthBufferSize.y - hitPoint.y;

    return (rayZmax >= sceneZmax - cb_zThickness) && (rayZmin <= sceneZmax);
}



vec3 PositionFromDepth(float depth) {
    float z = depth;

    vec4 clipSpacePosition = vec4(TexCoords * 2.0 - 1.0, -0.01, 1.0);
    vec4 viewSpacePosition = invProjection * clipSpacePosition;

    viewSpacePosition.xyz /= viewSpacePosition.w;

    return viewSpacePosition.xyz;
}



void main() {
    vec2 DepthBufferSize = textureSize(gDepth, 0);
    float Depth = texture(gDepth, TexCoords).r;

    //ray pointing towards negative Z axis (away from camera)
    // this is in clip space
    vec2 ndc = (2.0 * TexCoords ) - 1.0;
    vec4 viewRay = normalize(vec4(ndc.x, ndc.y, -Depth,1.0));
    //convert from clip space to view space
    viewRay = invProjection * viewRay;
    //prespective devision
    viewRay.xyz /= viewRay.w;

    vec3 WorldSpaceNormalVector = normalize(texture(gNormal, TexCoords).xyz);
    vec3 ViewSpaceNormalVector = normalize(vec3(View * vec4(WorldSpaceNormalVector, 0.0)));

    vec3 RayStartViewSpace = normalize(viewRay.xyz);
    vec3 RayDirectionViewSpace = normalize(reflect(RayStartViewSpace, ViewSpaceNormalVector));

    vec2 hitPixel = vec2(0.0);
    vec3 hitPoint = vec3(0.0);

    bool intersection = traceScreenSpaceRay(RayStartViewSpace, RayDirectionViewSpace, 1.0, DepthBufferSize, hitPixel, hitPoint);

    vec3 col = vec3(0.0);

    if (intersection) {
        col = texture(gColourShininess, hitPixel).xyz;
    }
    else{
        col = vec3(0.0);
    }

    FragColor = vec4(col,  1.0);
}