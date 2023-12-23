#version 330 core

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLight;
}fs_in;

out vec4 FragColor;

uniform sampler2D texture_diffuse0;
uniform sampler2D shadowMap;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

float caclualteShadow(vec4 FragPosLight, float bias)
{
   //tranfsforms fragment position in ragne from [0, 1]
    vec3 projCoords = FragPosLight.xyz / FragPosLight.w;
    projCoords = projCoords * 0.5 + 0.5;

    //get the closest depth value from the shadow map
    //closest object to the light
    float closestDepth = texture(shadowMap, projCoords.xy).w;
    
    //get the depth value of the current fragment 
    float currentDepth = projCoords.z;

    //compare if current depth value is bigger than the closest depth value
    // is true object is not in the shadow (1.0)
    // if false object is in the shadow (0.0)
    float shadow = 0;

    //this will be used for sampling neiborough texels in mipmap level 0
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);

    // creates 3x3 grid around the sampled texel
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            //sample the surounding texel
            //the multiplication by texelSize is necesary since the shadow map is in different resolution
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    //calculate the average 
    shadow /= 9.0;

    if(projCoords.z > 1.0)
        shadow = 0.0;   

    return shadow;

}

void main() 
{
    //----------
    // AMBIENT
    //----------
    vec3 ambient = vec3(texture(texture_diffuse0, fs_in.TexCoords)* 0.4);
    
    //--------
    // DIFFUSE
    //--------
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diffStrength = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = lightColor * diffStrength * vec3(texture(texture_diffuse0, fs_in.TexCoords));
    
    //--------
    //SPECULAR
    //--------
    vec3 texture_specular = lightColor;
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);

    float specStrength = pow(max(dot(normal, halfwayDir), 0.0),64.0);
    vec3 specular = texture_specular * specStrength;
    
    //--------
    // SHADOWS
    //--------
    float bias = max(0.09 * (1.0 - dot(normal, lightDir)), 0.05);

    float shadow = caclualteShadow(fs_in.FragPosLight, bias);
    vec3 result = (ambient + (1.0 - shadow) * (diffuse + specular)) * texture(texture_diffuse0, fs_in.TexCoords).rgb;

    //-------------
    // FINAL RESULT
    //-------------    
    FragColor = vec4(result,1.0);
}