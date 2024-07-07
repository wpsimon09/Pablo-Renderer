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

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}


void main() {
    vec4 colourShininess = texture(gColourShininess, TexCoords);
    vec4 N = texture(gNormal, TexCoords);

    vec2 MetalicRougness;

    //rougness
    MetalicRougness.r = colourShininess.r;
    //metalness
    MetalicRougness.g = N.a;

    if(MetalicRougness.r < 0.01)
            discard;

    vec3 viewNormal = vec3(vec4(N.rgb,1.0) * invView);
    vec3 viewPos = texture(gPosition, TexCoords).rgb;
    vec3 albedo = texture(gRenderedScene, TexCoords).rgb;

    float spec = N.a;

    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, MetalicRougness.g);
    vec3 Fresnel = fresnelSchlick(max(dot(normalize(viewNormal), normalize(viewPos)), 0.0), F0);

    FragColor = vec4(F0,1.0);
}
