#version 460 core

layout (location = 0) in vec3 aPos;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

void main(){
    glPosition = lightSpaceMatrix * model * vec4(aPos*1.0);
}