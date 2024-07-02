#version 460

layout (location = 0) out vec3 gPosition;
layout (location = 1) out vec3 gNormal;
layout (location = 2) out vec4 gShininessColour;
layout (location = 3) out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLight;
    mat3 TBN;
    float isModel;
    float hasEmission;
    float reciviesShadow;
    float hasNormalMap;
    float supportIBL;
}fs_in;

vec3 albedo;
float metallic;
float roughness;
float ao;
vec3 emmisive;

uniform vec3 camPos;
uniform vec3 lightColor;

uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D BRDFtexture;

uniform sampler2D _albedoMap;
uniform sampler2D _armMap;
uniform sampler2D _normalMap;
uniform sampler2D _aoMap;
uniform sampler2D _rougnessMetalnessMap;
uniform sampler2D _emmisionMap;

uniform sampler2DArray _materialTextures;

uniform sampler2D LTC;
uniform sampler2D LTC_Inverse;
uniform vec3 areaLightCorners[4];

const float LUT_SIZE = 64.0; // ltc_texture size
const float LUT_SCALE = (LUT_SIZE - 1.0) / LUT_SIZE;
const float LUT_BIAS = 0.5 / LUT_SIZE;

vec3 getNormalFromMap()
{
    vec3 tangentNormal = texture(_normalMap, fs_in.TexCoords).xyz * 2.0 - 1.0;

    vec3 Q1 = dFdx(fs_in.FragPos);
    vec3 Q2 = dFdy(fs_in.FragPos);
    vec2 st1 = dFdx(fs_in.TexCoords);
    vec2 st2 = dFdy(fs_in.TexCoords);

    vec3 N = normalize(fs_in.Normal);
    vec3 T = normalize(Q1 * st2.t - Q2 * st1.t);
    vec3 B = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

vec3 FresnelShlickRoughness(float cosTheta, vec3 F0, float roughness)
{
    return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}

vec3 IntegrateEdgeVec(vec3 v1, vec3 v2) {
    float x = dot(v1, v2);
    float y = abs(x);

    float a = 0.8543985 + (0.4965155 + 0.0145206 * y) * y;
    float b = 3.4175940 + (4.1616724 + y) * y;
    float v = a / b;

    float theta_sintheta = (x > 0.0) ? v : 0.5 * inversesqrt(max(1.0 - x * x, 1e-7)) - v;

    return cross(v1, v2) * theta_sintheta;
}

vec3 CalculateAreaLightLo(vec3 N, vec3 V, vec3 P, mat3 Minv, vec3 points[4], bool twoSided) {
    vec3 T1, T2;
    T1 = normalize(V - N * dot(V, N));
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
    bool behind = (dot(dir, lightNomrmal) < 0.0);

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

    float z = vsum.z / len;
    if (behind) {
        z = -z;
    }

    vec2 uv = vec2(z * 0.5f + 0.5f, len); // range [0, 1]
    uv = uv * LUT_SCALE + LUT_BIAS;

    float scale = texture(LTC, uv).w;

    float sum = len * scale;
    if (!behind) {
        sum = 0.0f;
    }
    vec3 Lo = vec3(sum, sum, sum);
    return Lo;
}


void main() {
    //-------------------------
    // GET VALUES FROM TEXTURES
    //-------------------------
    albedo =texture(_albedoMap, fs_in.TexCoords).rgb;
    //texture(_materialTextures, vec3(fs_in.TexCoords, 0.0)).rgb;
    if (fs_in.isModel == 1.0) {
        roughness = texture(_rougnessMetalnessMap, fs_in.TexCoords).g;
        metallic = texture(_rougnessMetalnessMap, fs_in.TexCoords).b;
        ao = texture(_aoMap, fs_in.TexCoords).r;
    } else {
        vec3 arm = texture(_armMap, fs_in.TexCoords).rgb;
        ao = arm.r;
        roughness = arm.g;
        metallic = arm.b;
    }
    if (fs_in.hasEmission == 1) {
        emmisive = texture(_emmisionMap, fs_in.TexCoords).rgb;
    }
    vec3 N = getNormalFromMap();


    //---------------------
    // ADDITIONAL VARIABLES
    //---------------------
    vec3 V = normalize(camPos - fs_in.FragPos);
    vec3 P = fs_in.FragPos;
    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, metallic);

    float NdotV = clamp(dot(N, V), 0.0, 1.0);
    vec3 R = reflect(-V, N);


//----------------
    // SAMPLE FORM LTC
    //----------------
    vec2 uv = vec2(roughness, sqrt(1.0f - NdotV));
    uv = uv * LUT_SCALE + LUT_BIAS;

    vec4 t1 = texture(LTC_Inverse, uv);
    vec4 t2 = texture(LTC, uv);

    mat3 Minv = mat3(
        vec3(t1.x, 0, t1.y),
        vec3(0, 1, 0),
        vec3(t1.z, 0, t1.w)
    );

    //------------------
    // ACCTUAL LIGHTNING
    //------------------
    vec3 diffuse = CalculateAreaLightLo(N, V, P, mat3(1.0), areaLightCorners, false);
    vec3 specular = CalculateAreaLightLo(N, V, P, Minv, areaLightCorners, false);

    specular *= albedo * t2.x + (1.0 - albedo) * t2.y;

    vec3 Lo = vec3(1.0);

    Lo = lightColor * ((specular) + (diffuse * albedo));

    //-----------
    // IBL PART
    //-----------
    vec3 ambient = vec3(0.0f);

    vec3 f;
    if(fs_in.supportIBL == 1){
        vec3 F = FresnelShlickRoughness(max(dot(N,V),0.0), F0, roughness);;
        vec3 kS = F;
        vec3 kD = vec3(1.0) - kS;
        kD *= 1.0 - metallic;

        vec3 irradiance = texture(irradianceMap, N).rgb;
        vec3 diff = irradiance * albedo;
        const float MAX_REFLECTION_LOD = 5.0;
        vec3 prefilterColor = textureLod(prefilterMap, R, roughness * MAX_REFLECTION_LOD).rgb;

        vec2 brdf = texture(BRDFtexture, vec2(max(dot(N,V), 0.0), roughness)).rg;
        vec3 spec = (prefilterColor * (kS * brdf.x +  brdf.y));
        f=spec;
        ambient = (kD * diff + spec) *(0.7);
    }
    else{
        ambient = albedo * 0.3;
    }



    vec3 result = ambient + Lo;

    if(fs_in.hasEmission == 1){
        result += emmisive;
    }

    //result = result / (result + vec3(1.0));

    FragColor = vec4(result, 1.0);

    gPosition = fs_in.FragPos.xyz;
    gNormal = N.rgb  ;
    gShininessColour.rgb = albedo.rgb;
    gShininessColour.a = roughness;
}