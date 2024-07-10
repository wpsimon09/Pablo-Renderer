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
float cb_zThickness;

// the camera's near z plane
float cb_nearPlaneZ;

// Step in horizontal or vertical pixels between samples. This is a float
// because integer math is slow on GPUs, but should be set to an integer >= 1.
float cb_stride;

// Maximum number of iterations. Higher gives better images but may be slow.
float cb_maxSteps;
// Maximum camera-space distance to trace before returning a miss.
float cb_maxDistance;

// More distant pixels are smaller in screen space. This
//value tells at what point to
// start relaxing the stride to give higher quality reflections for objects far from
// the camera.
float cb_strideZCutoff;

// the number of mip levels in the convolved color buffer
float cb_numMips;

// determines where to start screen edge fading of effect
float cb_fadeStart;

// determines where to end screen edge fading of effect
float cb_fadeEnd;

// padding for alignment
float cb_sslr_padding0;


float disatnceSqared(vec2 a, vec2 b){
    a -= b;
    return dot(a,a);
}

bool intersetcsDepthBuffer(float z, float minZ, float maxZ){
    float depthScale = min(1.0f, z* cb_strideZCutoff);
    z += cb_zThickness + mix(0.0f, 2.0f, depthScale);
    return (maxZ >= z) && (minZ - cb_zThickness <=z);
}


void main() {

    FragColor = vec4(texture(gPosition,TexCoords).rgb, 1.0);
}