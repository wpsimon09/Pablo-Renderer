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

uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D BRDFtexture;

uniform vec3 lightPositions[5];
uniform vec3 lightColors[5];
uniform vec3 camPos;

vec3  albedo;
float metallic;
float roughness;
float ao;
vec3 emmisive;

uniform sampler2D _albedoMap;
uniform sampler2D _metallnesMap;
uniform sampler2D _normalMap;
uniform sampler2D _rougnessMap;
uniform sampler2D _aoMap;
uniform sampler2D _emmisionMap;

const float PI = 3.14159265359;

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

vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(_normalMap, fs_in.TexCoords).xyz * 2.0 - 1.0;

    vec3 Q1  = dFdx(fs_in.FragPos);
    vec3 Q2  = dFdy(fs_in.FragPos);
    vec2 st1 = dFdx(fs_in.TexCoords);
    vec2 st2 = dFdy(fs_in.TexCoords);

    vec3 N   = normalize(fs_in.Normal);
    vec3 T  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

// N in the eqation
// N = normal vector
// H = halfway vector
float DistributionFunctionGGX(vec3 N, vec3 H, float roughtness)
{
    float a = roughness * roughtness;
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
    albedo = texture(_albedoMap, fs_in.TexCoords).rgb;
    metallic = texture(_rougnessMap, fs_in.TexCoords).b;
    roughness = texture(_rougnessMap, fs_in.TexCoords).g;
    ao = texture(_aoMap, fs_in.TexCoords).r;
    emmisive = texture(_emmisionMap, fs_in.TexCoords).rgb;

    //normal
    //vec3 N = normalize(fs_in.Normal);
    vec3 N = texture(_normalMap, fs_in.TexCoords).xyz;
    N = normalize(N * fs_in.TBN);
    //N = normalize(fs_in.Normal);
    //view direction;
    vec3 V = normalize(camPos - fs_in.FragPos);

    //reflect the view direction around the normal vector
    vec3 R = reflect(-V, N);
   
    //metalness of the material
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

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
        float NDF = DistributionFunctionGGX(N,H, roughness);
        float G = GeometrySmith(N,V,L, roughness);
        vec3 F = FresnelShlick(max(dot(H, V), 0.0), F0);

        //Cook tolerance
        //for working with metallic materials
        //specifiing the metallness of the object
        vec3 numerator = NDF * G * F;
        float denominator = 4.0 * max(dot(N,V), 0.0) * max(dot(N,L), 0.0);
        
        //calculate the specular component
        vec3 specular = numerator / max(denominator, 0.001);

        //calculate the ammount that gets refracted and what gets reflected
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;

        // if surface is metllic nullify the diffuse component
        kD *= 1.0 - metallic;

        //calculate the final rendering eqation
        float NdotL = max(dot(N,L), 0.0);
        Lo += (kD * albedo /PI + specular) * radiance * NdotL;
    }

    //----------------------
    // IMAGE BASED LIGHTING
    //----------------------
    vec3 F = FresnelShlickRoughness(max(dot(N,V),0.0), F0, roughness);
    
    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - metallic;

    vec3 irradiance = texture(irradianceMap, N).rgb;
    vec3 diffuse = irradiance * albedo ;
    
    const float MAX_REFLECTION_LOD = 4.0;
    vec3 prefilterColor = textureLod(prefilterMap, R, roughness * MAX_REFLECTION_LOD).rgb;

    vec2 brdf = texture(BRDFtexture, vec2(max(dot(N,V), 0.0), roughness)).rg;
    vec3 specular = prefilterColor * (kS * brdf.x +  brdf.y);
    
    vec3 ambient = (kD * diffuse + specular ) * ao ;
    ambient += ( 4.0 * emmisive);
    vec3 color = ambient + Lo;

    //HDR
    color = color / (color + vec3(1.0));
    
    // gamma corection
    //color = pow(color,vec3(1.0/2.2));

    FragColor = vec4(color, 1.0);

}