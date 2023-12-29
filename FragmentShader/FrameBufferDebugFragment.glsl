#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D attachment;

void main(){
    FragColor = vec4(0.0,1.0,0.0,1.0);
}