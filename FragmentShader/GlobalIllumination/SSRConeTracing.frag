#version 460

#define CONST_SPECULAR_EXPONENT 4

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D gDepth;
uniform sampler2D gNormal;
uniform sampler2D gRenderedScene;
uniform sampler2D gColourShininess;
uniform sampler2D gMetalnessRougness;

uniform sampler2D ConvolvedScene;
uniform sampler2D RayTracingBuffer;

float specPowerToConeAngle(float specularPower){
    if(specularPower >= exp2(CONST_SPECULAR_EXPONENT)){
        return 0.0;
    }
    const float xi = 0.2444f;
    float exponent = 1.0 /(specularPower + 1.0);
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
    float a2 = a*a;
    float fh2 = 4.0 * h * h;
    return (a*(sqrt(a2, fh2)-a))/(4.0 * h);
}

vec4 coneSampleWightColor(vec2 samplerPos, float mipChanel, float gloss){
    vec3 sampledColor = texture(ConvolvedScene, samplerPos, mipChanel).rgb;
    return vec4 (sampledColor * gloss, gloss);
}

float isoscaleTriangleNextAdjecent(float adjencentLength, float incircleRadius){
    return adjencentLength - (incircleRadius *2);
}

void main() {

    FragColor = vec4(0.0);
}