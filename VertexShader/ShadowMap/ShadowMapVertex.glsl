#version 460 core

layout (location = 0) in vec3 aPos;

uniform mat4 lightMatrix;
uniform mat4 model;

void main(){
    gl_Position = lightMatrix * model * vec4(aPos,1.0);
}