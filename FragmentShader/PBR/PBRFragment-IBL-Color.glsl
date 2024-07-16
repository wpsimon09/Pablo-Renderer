#version 330 core

layout (location = 0) out vec4 gPosition;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gShininessColour;
layout (location = 3) out vec2 gMetalnessRougness;
layout (location = 4) out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLight;
    mat3 TBN;
    float hasNormalMap;
    float supportIBL;
    float reciviesShadow;
}fs_in;


uniform vec3 lightPositions[5];
uniform vec3 lightColors[5];
uniform vec3 camPos;

uniform vec3 _valAlbedo;
uniform float _valMetallic;
uniform float _valRougness;
uniform float _valAo;

uniform sampler2D shadowMap;
uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D BRDFtexture;

const float PI = 3.14159265359;

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


// caclulate how much light geths reflected vs how much light gets refracted
//cosThete = angle we are looking at the surface
//F0 = how much surface reflects when looking directly at it (big database)
vec3 FresnelShlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 FresnelShlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}


// N in the eqation
// N = normal vector
// H = halfway vector
float DistributionFunctionGGX(vec3 N, vec3 H, float roughtness)
{
    float a = roughtness * roughtness;
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

float GeometryShclickGGX(float NdotVorL, float roughness)
{
    float r = (roughness + 1.0);
    //roughtness parameter based on type of light
    float k = (r * r)/8;

    //top part of the fraction
    float num = NdotVorL;

    //bottom part of the fraction
    float denom = NdotVorL * (1.0 - k) + k;

    return num/denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    //for view direction
    float NdotV = max(dot(N,V),0.0);
    float ggx2 = GeometryShclickGGX(NdotV, roughness);

    //for light direction
    float NdotL = max(dot(N,L), 0.0);
    float ggx1 = GeometryShclickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

void main()
{
    //sampler the texture maps
    vec3 N = fs_in.Normal;

    //normal
    //vec3 N = normalize(fs_in.Normal);
    //N = normalize(fs_in.Normal);
    //view direction;
    vec3 V = normalize(camPos - fs_in.FragPos);

    //reflect the view direction around the normal vector
    vec3 R = reflect(-V, N);

    //metalness of the material
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, _valAlbedo, _valMetallic);

    //result
    vec3 Lo = vec3(0.0);

    vec3 L;

    vec3 specular = vec3(0.0);

    for(int i = 0; i<5 ; i++)
    {
        //light direction
        L = normalize(lightPositions[i] - fs_in.FragPos);

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
        //for working with metallic materials
        //specifiing the metallness of the object
        vec3 numerator = NDF * G * F;
        float denominator = 4.0 * max(dot(N,V), 0.0) * max(dot(N,L), 0.0);

        //calculate the specular component
        specular = numerator / max(denominator, 0.001);

        //calculate the ammount that gets refracted and what gets reflected
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;

        // if surface is metllic nullify the diffuse component
        kD *= 1.0 - _valMetallic;

        //calculate the final rendering eqation
        float NdotL = max(dot(N,L), 0.0);
        Lo += (kD * _valAlbedo /PI + specular) * radiance * NdotL;
    }
    vec3 ambient;

    if(fs_in.supportIBL == 1){
        vec3 F = FresnelShlickRoughness(max(dot(N,V),0.0), F0, _valRougness);

        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - _valMetallic;

        vec3 irradiance = texture(irradianceMap, N).rgb;
        vec3 diffuse = irradiance * _valAlbedo ;

        const float MAX_REFLECTION_LOD = 4.0;
        vec3 prefilterColor = textureLod(prefilterMap, R, _valRougness * MAX_REFLECTION_LOD).rgb;

        vec2 brdf = texture(BRDFtexture, vec2(max(dot(N,V), 0.0), _valRougness)).rg;
        vec3 specular = prefilterColor * (kS * brdf.x +  brdf.y);

        ambient = (kD * diffuse + specular ) * 0.3 ;
    }else{
        ambient = (_valAlbedo * _valAo)*0.5;
    }

    vec3 color = ambient + Lo;

    //HDR
    color = color / (color + vec3(1.0));

    FragColor = vec4(color, 1.0);

    gPosition = vec4(fs_in.FragPos.xyz,1.0);
    gNormal = vec4(N.xyz,_valMetallic);
    gMetalnessRougness = vec2(_valMetallic, _valRougness);
    gShininessColour = vec4(color.rgb,  _valRougness);

}