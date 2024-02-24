#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D FragmentColor;

void main(){
    vec3 color = texture(FragmentColor, TexCoords).rgb;
    color = pow(color,vec3(1.0/2.2));
    FragColor = vec4(color,1.0);

}