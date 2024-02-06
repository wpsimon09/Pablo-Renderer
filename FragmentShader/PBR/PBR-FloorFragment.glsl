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

uniform sampler2D _albedoMap;
uniform sampler2D _metallnesMap;
uniform sampler2D _normalMap;
uniform sampler2D _roughnessMap;
uniform sampler2D _aoMap;
uniform sampler2D _displacementMap;

uniform vec3 lightPositions[5];
uniform vec3 lightColors[5];
uniform vec3 camPos;

const float PI = 3.14159265359;


vec2 ParalaxMapping(vec2 textureCoordinates, vec3 viewDir)
{
    float numOfLayers = 10;

    float layerDepth = 1 / numOfLayers;

    float currentLayerDepth  = 0.0f;

    vec2 P = viewDir.xy * 0.3;
    vec2 deltaTexCoords = P / numOfLayers;

    vec2 currentTexCoords = textureCoordinates;

    float currentDepthMapValue  = texture(_displacementMap, currentTexCoords).r;

    while(currentLayerDepth < currentDepthMapValue)
    {
        currentTexCoords -= deltaTexCoords;
        currentDepthMapValue = texture(_displacementMap, currentTexCoords).r;
        currentLayerDepth += layerDepth;
    }

    //get the textures coordinates before collision
    vec2 prevTexCoords = currentTexCoords + deltaTexCoords;

    //get the depth values before and afte the collision
    float afterDepth = currentDepthMapValue - currentLayerDepth;
    float beforeDepth = texture(_displacementMap, prevTexCoords).r - currentLayerDepth + layerDepth;

    //lineary interpola
    float weight = afterDepth / (afterDepth-beforeDepth);
    vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0 - weight);

    return finalTexCoords;
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

// caclulate how much light geths reflected vs how much light gets refracted
//cosThete = angle we are looking at the surface
//F0 = how much surface reflects when looking directly at it (big database)
vec3 FresnelShlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
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
    //view direction;
    vec3 V = normalize(camPos - fs_in.FragPos);

    vec2 TexCoords = ParalaxMapping(fs_in.TexCoords, V);

    vec3 albedo = pow(texture(_albedoMap, TexCoords).rgb, vec3(2.2));
    vec3 normal = getNormalFromMap();
    float metallic = texture(_metallnesMap, TexCoords).r;
    float roughness = texture(_roughnessMap, TexCoords).r;
    float ao = texture(_aoMap, TexCoords).r;

    //normal
    //vec3 N = fs_in.Normal;
    vec3 N = normal;

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
        vec3 radiance = lightColors[i];

        //DFG eqation
        float NDF = DistributionFunctionGGX(N,H, roughness);
        float G = GeometrySmith(N,V,L, roughness);
        vec3 F = FresnelShlick(max(dot(H, V), 0.0), F0);

        //Cook tolerance
        //for forking with metallic materials
        //specifiing the metallness of the object
        vec3 numerator = NDF * G * F;
        float denominator = 4.0 * max(dot(N,V), 0.0) * max(dot(N,L), 0.0) + 0.0001;

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

    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = Lo + ambient;

    //HDR
    color = color/ (color + vec3(1.0));

    // gamma corection
    color = pow(color,vec3(1.0/2.2));

    FragColor = vec4(color, 1.0);
}