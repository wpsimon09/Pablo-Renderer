#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D FragmentColor;

void main(){
    FragColor = vec4(texture(FragmentColor, TexCoords).rgba);
}