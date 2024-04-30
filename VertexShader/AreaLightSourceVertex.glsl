#version 460 core

layout (location = 0) in vec3 aPos;

uniform vec3 lightColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 areaLightColor;

void main()
{
    areaLightColor = lightColor;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}