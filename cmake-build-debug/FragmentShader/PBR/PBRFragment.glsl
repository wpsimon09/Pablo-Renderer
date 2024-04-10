#version 330 core

out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLight;
    mat3 TBN;
    float hasNormalMap;
}fs_in;

uniform vec3 lightPositions[5];
uniform vec3 lightColors[5];
uniform vec3 camPos;

uniform vec3 _valAlbedo;
uniform float _valMetallic;
uniform float _valRougness;
uniform float _valAo;

const float PI = 3.14159265359;

// caclulate how much light geths reflected vs how much light gets refracted
//cosThete = angle we are looking at the surface
//F0 = how much surface reflects when looking directly at it (big database)
vec3 FresnelShlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);   
}

// N in the eqation
// N = normal vector
// H = halfway vector
float DistributionFunctionGGX(vec3 N, vec3 H, float roughtness)
{
    float a = _valRougness * roughtness;
    float a2 = a*a;
    float NdotH = max(dot(N,H),0.0);
    float NdotH2 = NdotH * NdotH;

    //top part of fraction
    float num = a2;
    
    //bottom part of the fraction
    float denom = (NdotH2 * (a2 -1.0) + 1.0);
    denom = PI * denom * denom;

    return num/denom;
}

float GeometryShclickGGX(float NdotVorL, float _valRougness)
{
    float r = (_valRougness + 1.0);
    //roughtness parameter based on type of light
    float k = (r * r)/8;

    //top part of the fraction
    float num = NdotVorL;

    //bottom part of the fraction
    float denom = NdotVorL * (1.0 - k) + k;

    return num/denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float _valRougness)
{
    //for view direction
    float NdotV = max(dot(N,V),0.0);
    float ggx2 = GeometryShclickGGX(NdotV, _valRougness);
    
    //for light direction
    float NdotL = max(dot(N,L), 0.0);
    float ggx1 = GeometryShclickGGX(NdotL, _valRougness);

    return ggx1 * ggx2;
}

void main()
{
    //normal
    vec3 N = normalize(fs_in.Normal);
    
    //view direction;
    vec3 V = normalize(camPos - fs_in.FragPos);
    
    //metalness of the material
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, _valAlbedo, _valMetallic);

    //result
    vec3 Lo = vec3(0.0);

    for(int i = 0; i<5 ; i++)
    {
        //light direction
        vec3 L = normalize(lightPositions[i] - fs_in.FragPos);
        
        //hallfway vector;
        vec3 H = normalize(V + L);

        //attentuation
        float distance = length(lightPositions[i] - fs_in.FragPos);
        float attentuation = 1.0/(distance * distance);
        vec3 radiance = lightColors[i] * attentuation;

        //DFG eqation
        float NDF = DistributionFunctionGGX(N,H, _valRougness);
        float G = GeometrySmith(N,V,L, _valRougness);
        vec3 F = FresnelShlick(max(dot(H, V), 0.0), F0);

        //Cook tolerance
        //for forking with _valMetallic materials
        //specifiing the metallness of the object
        vec3 numerator = NDF * G * F;
        float denominator = 4.0 * max(dot(N,V), 0.0) * max(dot(N,L), 0.0);
        
        //calculate the specular component
        vec3 specular = numerator / max(denominator, 0.001);

        //calculate the ammount that gets refracted and what gets reflected
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;

        // if surface is metllic nullify the diffuse component
        kD *= 1.0 - _valMetallic;

        //calculate the final rendering eqation
        float NdotL = max(dot(N,L), 0.0);
        Lo += (kD * _valAlbedo /PI + specular) * radiance * NdotL;
    }

    vec3 ambient = vec3(0.03) * _valAlbedo * _valAo;
    vec3 color = ambient + Lo;

    //HDR
    color = color/ (color + vec3(1.0));
    
    // gamma corection
    color = pow(color,vec3(1.0/2.2));

    FragColor = vec4(color, 1.0);
}