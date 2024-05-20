#version 460

#define MAX_POST_PROCESING_TEXTURES 10

out vec4 FragColor;

in vec2 TexCoords;

uniform int postProcessCount;

uniform sampler2D postProcessingEffect[MAX_POST_PROCESING_TEXTURES];

void main() {

    vec3 colorPrevious = texture(previousResult, TexCoords).rgb;

    vec3 colorNew = texture(newResult, TexCoords).rgb;

    FragColor = vec4(colorPrevious + colorNew,1.0);
}