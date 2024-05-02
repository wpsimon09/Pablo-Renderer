#version 460 core


out vec4 FragColor;

in vec3 areaLightColor;

void main(){
    FragColor = vec4(areaLightColor.rgb, 1.0);
}
