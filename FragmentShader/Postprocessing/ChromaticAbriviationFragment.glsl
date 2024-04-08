#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D FragmentColor;

uniform vec2 mouseFocusPoint;

float redOffset   =  0.009;
float greenOffset =  0.006;
float blueOffset  = -0.006;


void main(){
    //vec3 color = texture(FragmentColor, TexCoords).rgb;

    vec2 direction =  TexCoords - mouseFocusPoint;

    int pixelSize = 8;

    vec4 color;

    color.r  = texture(FragmentColor, TexCoords + (direction * vec2(redOffset  ))).r;
    color.g  = texture(FragmentColor, TexCoords + (direction * vec2(greenOffset))).g;
    color.ba = texture(FragmentColor, TexCoords + (direction * vec2(blueOffset ))).ba;


    FragColor = color;
}