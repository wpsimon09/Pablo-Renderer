#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangetn;
layout (location = 4) in vec3 aBitangent;
layout (location = 5) in mat4 instancedModel;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    mat3 TBN;
    float hasNormalMap;
}vs_out;

uniform mat4 projection;
uniform mat4 view;

uniform float hasNormalMap;

void main()
{
    mat4 model = instancedModel;
    mat3 normalMatrix = transpose(inverse(mat3(model)));

    // transform the vectors to the world space 
    vec3 T = normalize(normalMatrix * aTangetn);
    vec3 N = normalize(normalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    // create the TBN matrix
    mat3 TBN = transpose(mat3(T,B,N));

    vs_out.FragPos =  vec3(model * vec4(aPos, 1.0));
    vs_out.TexCoords = aTexCoords;
    vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;
    vs_out.hasNormalMap = hasNormalMap;
    vs_out.TBN = TBN;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
