#version 460

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

uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D BRDFtexture;
uniform sampler2D shadowMap;

uniform vec3 camPos;
uniform vec3  _valAlbedo;
uniform float _valMetallic;
uniform float _valRougness;
uniform float _valAo;

uniform vec3 lightColor;

uniform sampler2D LTC;
uniform sampler2D LTC_Inverse;

uniform vec3 areaLightCorners[4];

const float LUT_SIZE  = 64.0; // ltc_texture size
const float LUT_SCALE = (LUT_SIZE - 1.0)/LUT_SIZE;
const float LUT_BIAS  = 0.5/LUT_SIZE;

vec3 FresnelShlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - (roughness*roughness)), F0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

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

vec3 IntegrateEdgeVec(vec3 v1, vec3 v2){
    float x = dot(v1, v2);
    float y = abs(x);

    float a = 0.8543985 + (0.4965155 + 0.0145206*y)*y;
    float b = 3.4175940 + (4.1616724 + y)*y;
    float v = a / b;

    float theta_sintheta = (x > 0.0) ? v : 0.5*inversesqrt(max(1.0 - x*x, 1e-7)) - v;

    return cross(v1, v2)*theta_sintheta;
}

vec3 CalculateAreaLightLo(vec3 N, vec3 V, vec3 P, mat3 Minv, vec3 points[4], bool twoSided){
    vec3 T1, T2;
    T1 = normalize(V-N * dot(V, N));
    T2 = cross(N, T1);

    Minv = Minv * transpose(mat3(T1, T2, N));

    vec3 L[4];

    // transform polygon from LTC back to origin Do (cosine weighted)
    L[0] = Minv * (points[0] - P);
    L[1] = Minv * (points[1] - P);
    L[2] = Minv * (points[2] - P);
    L[3] = Minv * (points[3] - P);

    // check if the shading point is behind the light
    vec3 dir = points[0] - P;

    vec3 lightNomrmal = cross(points[1] - points[0], points[3] - points[0]);
    bool behind = (dot(dir, lightNomrmal)<0.0);

    // cos weighted space
    L[0] = normalize(L[0]);
    L[1] = normalize(L[1]);
    L[2] = normalize(L[2]);
    L[3] = normalize(L[3]);

    // integrate
    vec3 vsum = vec3(0.0);
    vsum += IntegrateEdgeVec(L[0], L[1]);
    vsum += IntegrateEdgeVec(L[1], L[2]);
    vsum += IntegrateEdgeVec(L[2], L[3]);
    vsum += IntegrateEdgeVec(L[3], L[0]);

    float len = length(vsum);

    float z = vsum.z/len;
    if(behind){
        z = -z;
    }

    vec2 uv = vec2(z*0.5f + 0.5f, len); // range [0, 1]
    uv = uv*LUT_SCALE + LUT_BIAS;

    float scale = texture(LTC,uv).w;

    float sum = len*scale;
    if(!behind){
        sum=0.0f;
    }
    vec3 Lo = vec3(sum ,sum, sum);
    return Lo;
}

void main() {
    vec3 N = normalize(fs_in.Normal);
    vec3 V = normalize(camPos - fs_in.FragPos);
    vec3 P = fs_in.FragPos;
    vec3 R = reflect(-V, N);

    vec3 F0 = vec3(0.04);
    F0 = mix(F0, _valAlbedo, _valMetallic);


//reflected view direction around normal vector
    float NdotV = clamp(dot(N,V), 0.0, 1.0);

    //use roughness and cosine of view direction around normal vector to sample the precomputed matrices
    vec2 uv = vec2(_valRougness, sqrt(1.0f - NdotV));
    uv = uv*LUT_SCALE + LUT_BIAS;

    vec4 t1 = texture(LTC_Inverse, uv);

    vec4 t2 = texture(LTC, uv);

    mat3 Minv = mat3(
        vec3(t1.x, 0, t1.y),
        vec3(   0, 1,    0),
        vec3(t1.z, 0, t1.w)
    );


    vec3 diffuse = CalculateAreaLightLo(N,V,P,mat3(1.0),areaLightCorners,false);
    vec3 specular = CalculateAreaLightLo(N,V,P, Minv, areaLightCorners, false);

    specular *= _valAlbedo*t2.x + (1.0 - _valAlbedo)*t2.y;

    vec3 Lo = vec3(1.0);
    Lo = lightColor * ((specular) + (diffuse * _valAlbedo));

    //----------------------
    // IBL and SHADOW PART
    //----------------------
    vec3 ambient = vec3(0.0f);
    float shadow = 0.3;
    float shadowBias = 0.02;
    if(fs_in.reciviesShadow == 1){
        shadow = caclualteShadow(fs_in.FragPosLight, shadowBias);
    }

    if(fs_in.supportIBL == 1){
        vec3 F = FresnelShlickRoughness(max(dot(N,V),0.0), F0, _valRougness);;
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - _valMetallic;

        vec3 irradiance = texture(irradianceMap, N).rgb;
        vec3 diff = irradiance * _valAlbedo;

        const float MAX_REFLECTION_LOD = 4.0;
        vec3 prefilterColor = textureLod(prefilterMap, R, _valRougness * MAX_REFLECTION_LOD).rgb;

        vec2 brdf = texture(BRDFtexture, vec2(max(dot(N,V), 0.0), _valRougness)).rg;
        vec3 spec = prefilterColor * (kS * brdf.x +  brdf.y);

        ambient = (kD * diff + spec ) *(1-shadow);
    }
    else{
        ambient = (_valAlbedo * _valAo)*(1-shadow);
    }

    vec3 finalColor = ambient + Lo;

    FragColor = vec4(finalColor, 1.0);

    gPosition = vec4(fs_in.FragPos.xyz,1.0);
    gNormal = vec4(N.xyz, 1.0);
    gShininessColour = vec4(finalColor.rgb ,1.0);
    gMetalnessRougness = vec2(_valMetallic, _valRougness);

}
