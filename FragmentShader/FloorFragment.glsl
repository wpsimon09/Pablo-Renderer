#version 330 core

layout (location = 3) out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLight;
}fs_in;


void main()
{
    vec3 color = vec3(1.0);

    FragColor = vec4(color, 0.7 );
}