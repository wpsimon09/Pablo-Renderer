#version 330 core

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLight;
    mat3 TBN;

    float hasNormalMap;
}fs_in;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform sampler2D texture_diffuse0;
uniform sampler2D texture_normal0;
uniform sampler2D texture_specular0;

uniform vec3 lightColor;

void main() 
{
    //----------
    // AMBIENT
    //----------
    vec3 ambient = vec3(texture(texture_diffuse0, fs_in.TexCoords)* 0.6);
    
    //--------
    // DIFFUSE
    //--------
    vec3 normal;
    if(fs_in.hasNormalMap == 1.0)
    {
        //sample normal vectors from the texture
        normal = texture(texture_normal0, fs_in.TexCoords).rgb;
        
        //convert from range [0,1] to the range [-1, 1]
        normal = normalize(normal * 2.0 - 1.0) * fs_in.TBN;   
    }
    else 
        normal = normalize(fs_in.Normal);

    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diffStrength = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = lightColor * diffStrength * vec3(texture(texture_diffuse0, fs_in.TexCoords));
    
    //--------
    //SPECULAR
    //--------
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    float specStrength = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);

    specStrength = pow(max(dot(normal, halfwayDir), 0.0),64.0);
    vec3 specular = lightColor * specStrength * vec3(texture(texture_specular0, fs_in.TexCoords));

    vec3 result = ambient + diffuse + specular;

    //-------------
    // FINAL RESULT
    //-------------    
    FragColor = vec4(result,1.0);
}