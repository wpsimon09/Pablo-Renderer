#version 460

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D gDepth;
uniform sampler2D gNormal;
uniform sampler2D ConvolvedScene;
uniform sampler2D rayTracingBuffer;
uniform sampler2D gMetalnessRougness;


void main() {
    FragColor = vec4(0.0);
}