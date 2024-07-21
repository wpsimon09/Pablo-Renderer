#version 460

out vec4 FragCol;
in vec2 TexCoords;

uniform float texOffSetY;
uniform sampler2D Scene;


float kernel[7] = float[](0.128, 0.144, 0.155, 0.160, 0.155, 0.144, 0.128);

void main() {
    vec4 color = vec4(0.0);
    for (int i = -3; i <= 3; ++i) {
        color += texture(Scene  , TexCoords + vec2(0.0, i)*texOffSetY) * kernel[i + 3];
    }
    FragCol = color;

}