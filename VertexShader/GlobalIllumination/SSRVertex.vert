#version 460


layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 projection;

out vec2 TexCoords;
out mat4 Pojection;

void main()
{
    Pojection = projection;
    TexCoords = aTexCoords;
    gl_Position = vec4(aPos, 1.0);
}
