#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangetn;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in mat4 instancedModel;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform mat4 lightMatrix;

uniform float hasNormalMap;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLight;
    mat3 TBN;

    float hasNormalMap;
}vs_out;

void main()
{
    mat3 normalMatrix = transpose(inverse(mat3(instancedModel)));

    // transform the vectors to the world space 
    vec3 T = normalize(normalMatrix * aTangetn);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    // create the TBN matrix
    mat3 TBN = transpose(mat3(T,B,N));

    vs_out.FragPos =  vec3(instancedModel * vec4(aPos, 1.0));
    vs_out.TexCoords = aTexCoords;
    vs_out.Normal = transpose(inverse(mat3(instancedModel))) * aNormal;
    vs_out.FragPosLight = lightMatrix * vec4(vs_out.FragPos ,1.0);
    vs_out.hasNormalMap = hasNormalMap;
    vs_out.TBN = TBN;

    gl_Position = projection * view * instancedModel * vec4(aPos, 1.0);
}
