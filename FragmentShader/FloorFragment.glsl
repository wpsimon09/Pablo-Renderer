#version 330 core

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLight;
}fs_in;

out vec4 FragColor;

uniform sampler2D texture_diffuse0;

void main()
{
    //----------
    // AMBIENT
    //----------
    vec4 floorTexture = texture(texture_diffuse0, fs_in.TexCoords).rgba;

    //-------------
    // FINAL RESULT
    //-------------    
    FragColor = vec4(1.0,1.0,1.0, 1.0);
}