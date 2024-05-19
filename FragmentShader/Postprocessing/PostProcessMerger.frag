#version 460

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D previousResult;

uniform sampler2D newResult;

void main() {

    vec3 colorPrevious = texture(previousResult, TexCoords).rgb;

    vec3 colorNew = texture(newResult, TexCoords).rgb;

    FragColor = vec4(colorPrevious + colorNew,1.0);
}