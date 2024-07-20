#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D FragmentColor;

uniform vec2 mouseFocusPoint;

float redOffset   =  0.009;
float greenOffset =  0.006;
float blueOffset  = -0.006;


void main(){
    vec3 color = textureLod(FragmentColor, TexCoords,0).rgb;

    FragColor = vec4(color,1.0);
}