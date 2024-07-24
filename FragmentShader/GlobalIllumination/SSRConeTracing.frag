#version 460

#define CONST_SPECULAR_EXPONENT 8

in vec2 TexCoords;

out vec4 FragColor;

uniform float maxMipNum;
uniform float maxSamples;

uniform sampler2D gPosition;
uniform sampler2D gDepth;
uniform sampler2D gNormal;
uniform sampler2D gRenderedScene;
uniform sampler2D gColourShininess;
uniform sampler2D gMetalnessRougness;

uniform sampler2D ConvolvedScene;
uniform sampler2D RayTracingBuffer;

uniform mat4 Projection;
uniform mat4 invProjection;

uniform mat4 View;
uniform mat4 invView;

float roughnessToSpecularPower(float roughness) {

    float specularPower = (2 / (max(pow(roughness,4), 0.001)))-2 ;

    return roughness*roughness;
}


float specPowerToConeAngle(float specularPower){
    if(specularPower >= exp2(CONST_SPECULAR_EXPONENT)){
        return 0.0;
    }
    const float xi = 0.244;
    float exponent = 1.0 /(max(specularPower,0.001) );
    return acos(pow(xi, exponent));
}

//Calculates the oposite site of the Isoscale triangle
float isocaleTriangleOpposite(float adjecentLength, float coneTheta){
    return 2.0 * tan(coneTheta) * adjecentLength;
}

// Calvulates in radius of the isoscale tirangle (circle that touches arr 3 sides)
// a - adjecent side of the isoscale triangle
// h - hieight of the ajencent triangle
float isoscalesTriangleInRadius(float a, float h){
    float a2  = a*a;
    float fh2 = 4.0 * h * h;
    return (a*(sqrt(a2 + fh2)-a))/(4.0 * h);
}

vec4 coneSampleWightColor(vec2 samplerPos, float mipChanel, float gloss){
    vec3 sampledColor = textureLod(ConvolvedScene, samplerPos,0).rgb;
    return vec4 (sampledColor ,1.0);
}

float isoscaleTriangleNextAdjecent(float adjencentLength, float incircleRadius){
    return adjencentLength - (incircleRadius *2);
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

void main() {
    vec4 raySS = texture(RayTracingBuffer, TexCoords).xyzw;

    if(raySS.w <= 0.0){
        return;
    }
    float depth = texture(gDepth, TexCoords).r;
    vec3 positionSS = vec3(TexCoords, depth);

    vec2 depthBufferSize = textureSize(gDepth,0);

    vec3 positionVS = texture(gPosition, TexCoords).rgb;
    positionVS = vec3( View * vec4(positionVS, 1.0));

    vec3 toPositionVS = normalize(positionVS);
    vec3 normalsVS = normalize(vec3(vec4(texture(gNormal, TexCoords).rgb, 1.0)*invView));

    vec4 specularAll = texture(gMetalnessRougness, TexCoords);
    float gloss = 1.0 - specularAll.a;
    float specularPower = roughnessToSpecularPower(specularAll.a);

    float coneTheta = specPowerToConeAngle(specularPower) * 0.5;

    //ray start position (positionSS) and ray hit position in screen space
    // deltaP is vector from orgin to hit coordinates
    vec2 deltaP = raySS.xy - positionSS.xy;
    float adjencentLength = length(deltaP.xy);
    vec2 adjecentUnit = normalize(deltaP);

    vec4 totalColor = vec4(0.0);
    float remainingAlpha = 1.0;
    float maxMipLevel = maxMipNum;
    float glossMult = gloss;

    float mipChannel;
    vec2 samplePos;
    float incircleSize;
    float oppositeLength;
    //cone tracing using ScreenSpace Iscale triangles
    for(int i = 0; i<maxSamples; i++) {
        oppositeLength = isocaleTriangleOpposite(adjencentLength, coneTheta);
        incircleSize   = isoscalesTriangleInRadius(adjencentLength, oppositeLength);

        //retrieves sample position in Screen Space
        samplePos = positionSS.xy + adjecentUnit *(adjencentLength - incircleSize);

        mipChannel = clamp(log2(incircleSize * max(depthBufferSize.x, depthBufferSize.y) ) ,0.0, maxMipLevel);

        vec4 newColor = coneSampleWightColor(samplePos, mipChannel, glossMult);

        remainingAlpha -= newColor.a;
        if(remainingAlpha < 0.0){
            newColor *= (1.0 - abs(remainingAlpha));
        }
        totalColor += newColor;

        if(totalColor.a >= 1.0){
            break;
        }

        //adjencentLength = isoscaleTriangleNextAdjecent(adjencentLength, incircleSize);
        //glossMult *= gloss;
    }

    vec3 toEye = -toPositionVS;
    vec3 specular = fresnelSchlick(abs(dot(normalsVS, toEye)), specularAll.rgb);

    //totalColor.rgb *=specular;

    //totalColor = texture(gColourShininess, raySS.xy);

    vec3 color = texture(gColourShininess, raySS.xy).rgb;

    FragColor = vec4(mix(texture(gRenderedScene, TexCoords).rgb,raySS.rgb, 0.5),1.0);
}