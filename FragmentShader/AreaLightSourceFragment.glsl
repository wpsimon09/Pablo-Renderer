#version 460 core

in vec3 areaLightColor;

out vec4 FragColor;

void main(){
    FragColor = vec4(areaLightColor, 1.0);
}
