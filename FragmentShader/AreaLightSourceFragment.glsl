#version 460 core


layout (location = 3) out vec4 FragColor;

uniform vec3 lightColor;

void main(){
    FragColor = vec4(lightColor, 1.0);
}
