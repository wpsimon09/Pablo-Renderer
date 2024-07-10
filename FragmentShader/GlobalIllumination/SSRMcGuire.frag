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
float cb_zThickness = 0.2;

// the camera's near z plane
float cb_nearPlaneZ = 0.1;

float cb_farPlaneZ = 200;

// Step in horizontal or vertical pixels between samples. This is a float
// because integer math is slow on GPUs, but should be set to an integer >= 1.
float cb_stride = 0.2;

// Maximum number of iterations. Higher gives better images but may be slow.
float cb_maxSteps = 20;
// Maximum camera-space distance to trace before returning a miss.
float cb_maxDistance = 30;

// More distant pixels are smaller in screen space. This
//value tells at what point to
// start relaxing the stride to give higher quality reflections for objects far from
// the camera.
float cb_strideZCutoff = 20;

// the number of mip levels in the convolved color buffer
float cb_numMips = 0;

// determines where to start screen edge fading of effect
float cb_fadeStart = 200;

// determines where to end screen edge fading of effect
float cb_fadeEnd = 200;

// padding for alignment
float cb_sslr_padding0 = 0.2;


float linearizeDepth(float depth) {
    return (2.0 * cb_nearPlaneZ) / (cb_farPlaneZ + cb_nearPlaneZ - depth * (cb_farPlaneZ - cb_nearPlaneZ));
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

float linearDepthTexelFetch(vec2 hitPixel){
    return linearizeDepth(texture(gDepth, hitPixel).r);
}

bool traceScreenSpaceRay(vec3 csOrigin, vec3 csDir, float jitter, out vec2 hitPixel, out vec3 hitPoint) {
    float rayLength = ((csOrigin.z + csDir.z) * cb_maxDistance < cb_nearPlaneZ) ?
    (cb_nearPlaneZ - csOrigin.z) / csDir.z : cb_maxDistance;
    vec3 csEndPoint = csOrigin + csDir * rayLength;

    vec4 H0 = vec4(csOrigin, 1.0) * Projection;
    H0.xy *= cb_depthBufferSize;

    vec4 H1 = vec4(csEndPoint, 1.0) * Projection;
    H1.xy *= cb_depthBufferSize;

    float k0 = 1.0 / H0.w;
    float k1 = 1.0 / H1.w;

    vec3 Q0 = csOrigin * k0;
    vec3 Q1 = csEndPoint * k1;

    vec2 P0 = H0.xy * k0;
    vec2 P1 = H1.xy * k1;

    vec2 delta = P1 - P0;
    bool permute = false;
    if (abs(delta.x) < abs(delta.y)) {
        permute = true;
        delta = delta.yx; // Fix: Correct permutation
        P0 = P0.yx;
        P1 = P1.yx;
    }

    float stepDir = sign(delta.x);
    float invdx = stepDir / delta.x;

    vec3 dQ = (Q1 - Q0) * invdx;
    float dk = (k1 - k0) * invdx;
    vec2 dP = vec2(stepDir, delta.y * invdx);

    float strideScale = 1.0 - min(1.0, csOrigin.z * cb_strideZCutoff);
    float stride = 1.0 + strideScale * cb_stride;

    dP *= stride;
    dQ *= stride;
    dk *= stride;
    P0 += dP * jitter;
    Q0 += dQ * jitter;
    k0 += dk * jitter;

    vec4 PQK = vec4(P0, Q0.z, k0);
    vec4 dPQK = vec4(dP, dQ.z, dk);
    vec3 Q = Q0;

    float end = P1.x * stepDir;
    float stepCount = 0.0;
    float prevZMaxEstimate = csOrigin.z;
    float rayZmin = prevZMaxEstimate;
    float rayZmax = prevZMaxEstimate;
    float sceneZmax = rayZmax + 100.0;

    while (((PQK.x * stepDir) <= end) &&
    (stepCount < cb_maxSteps) &&
    !intersetcsDepthBuffer(sceneZmax, rayZmin, rayZmax) &&
    (sceneZmax != 0.0)) {
        stepCount++;
        rayZmin = prevZMaxEstimate;
        rayZmax = (dPQK.z * 0.5 + PQK.z) / (dPQK.w * 0.5 + PQK.w);
        if (rayZmin > rayZmax) {
            swap(rayZmin, rayZmax);
        }
        hitPixel = permute ? PQK.yx : PQK.xy;
        sceneZmax = linearDepthTexelFetch(hitPixel);
        PQK += dPQK;
    }

    Q.xy += dQ.xy * stepCount;
    hitPoint = Q * (1.0 / PQK.w);

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
    normalVS = normalize(vec3(vec4(normalVS, 1.0) * View));

    float depth = texture(gDepth, TexCoords).r;
    vec3 rayOriginVS = PositionFromDepth(depth);
    vec3 rayDirectionVS = normalize(reflect(rayOriginVS, normalVS));

    vec2 hitPixel;
    vec3 hitPoint;
    bool intersection = traceScreenSpaceRay(rayOriginVS, rayDirectionVS, 1.0, hitPixel, hitPoint);

    if (intersection) {
        FragColor = vec4(texture(gColourShininess, hitPixel)); // Replace with SSR color calculation
    } else {
        FragColor = vec4(0.0, 0.0, 0.0, 1.0);
    }
}