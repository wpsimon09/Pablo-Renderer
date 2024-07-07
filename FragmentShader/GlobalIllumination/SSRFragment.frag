#version 460

uniform sampler2D gNormal;
uniform sampler2D gPosition;
uniform sampler2D gColourShininess;
uniform sampler2D gRenderedScene;

uniform mat4 Projection;
uniform mat4 invProjection;

uniform mat4 View;
uniform mat4 invView;

in vec2 TexCoords;

out vec4 FragColor;

const float step = 0.1;
const float minRayStep = 0.1;
const float maxSteps = 30;
const int numBinarySearchSteps = 5;
const float reflectionSpecularFalloffExponent = 3.0;

float Metallic;

#define Scale vec3(.8, .8, .8)
#define K 19.19

void main() {
    vec4 colourShininess = texture(gColourShininess, TexCoords);
    vec4 normalMetalness = texture(gNormal, TexCoords);

    vec2 MetalicRougness;
    MetalicRougness.r = colourShininess.r;
    MetalicRougness.g = normalMetalness.a;

    if(MetalicRougness.r < 0.01)
            discard;


    FragColor = texture(gNormal,TexCoords);
}
