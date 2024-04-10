#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLight;
} vs_out;


uniform mat4 lightMatrix;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    
    vs_out.FragPos =  vec3(model * vec4(aPos, 1.0));
    vs_out.TexCoords = aTexCoords;
    vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;
    vs_out.FragPosLight = lightMatrix * vec4(vs_out.FragPos ,1.0);
}
