#version 460

uniform sampler2D gNormal;
uniform sampler2D gPosition;
uniform sampler2D gColourShininess;
uniform sampler2D gRenderedScene;
uniform sampler2D gDepth;

uniform mat4 Projection;
uniform mat4 invProjection;

uniform mat4 View;
uniform mat4 invView;

uniform vec3 cameraPosition;

uniform float ReflectionVecScale;
uniform float MaxSamplerCount;
uniform float MaxMarchStep;
uniform float MaxBinarySearchSteps;
uniform float MidRaySampleWeight;


uniform float NearPlane;
uniform float FarPlane;

precision highp float;
precision highp int;

in vec2 TexCoords;

out vec4 FragColor;

vec3 BinarySearch(in vec3 RaySample, in vec3 PreviousRaySample){
    vec3 MinRaySample = PreviousRaySample;

    vec3 MaxRaySample = RaySample;

    vec3 MidRaySample;

    for(int i = 0; i < MaxBinarySearchSteps; i++){
        MidRaySample = mix(MinRaySample, MaxRaySample, 0.5);
        float ZBufferVal = texture(gDepth, MidRaySample.xy).r;

        if(MidRaySample.z > ZBufferVal){
            MaxRaySample = MidRaySample;
        } else {
            MinRaySample = MidRaySample;
        }
    }

    return MidRaySample;
}

bool RayMarch(
    vec3 ScreenSpaceReflectionVec,
    vec3 ScreenSpacePosition,
out vec3 ReflectionColor
){
    vec3 PrevRaySample = ScreenSpacePosition;

    vec3 RaySample;
    float ZBufferVal;

    for(int RayStepIndex = 0; RayStepIndex < MaxSamplerCount ; RayStepIndex++){
        RaySample = (RayStepIndex * MaxMarchStep) * ScreenSpaceReflectionVec + ScreenSpacePosition;

        ZBufferVal = texture(gDepth, RaySample.xy).r;

        if(RaySample.z > ZBufferVal){
            vec3 IntersectionSample = BinarySearch(RaySample, PrevRaySample);

            vec2 texCoords = IntersectionSample.xy / vec2(textureSize(gDepth, 0));
            ReflectionColor = texture(gColourShininess, TexCoords).rgb;

            return true;
        }
        PrevRaySample = RaySample;
    }
    return false;
}

vec3 PositionFromDepth(float depth) {
    float z = depth * 2.0 - 1.0;

    vec4 clipSpacePosition = vec4(TexCoords * 2.0 - 1.0, z, 1.0);
    vec4 viewSpacePosition = invProjection * clipSpacePosition;

    viewSpacePosition.xyz /= viewSpacePosition.w;

    return viewSpacePosition.xyz;
}

void main() {

    vec2 DepthBufferSize = textureSize(gDepth, 0);
    float Depth = texture(gDepth, TexCoords).r;

    vec3 WorldSpaceNormalVector = normalize(texture(gNormal, TexCoords).xyz);
    vec3 ViewSpaceNormalVector = normalize(vec3(View * vec4(WorldSpaceNormalVector, 0.0)));

    vec3 RayStartViewSpace = normalize(PositionFromDepth(Depth));
    vec3 RayDirectionViewSpace = normalize(reflect(RayStartViewSpace, ViewSpaceNormalVector));

    vec3 OutReflectionColor;

        bool intersect = RayMarch(RayDirectionViewSpace, RayStartViewSpace.xyz, OutReflectionColor);

    vec4 Result = vec4(0.0f);

    Result = vec4(RayDirectionViewSpace,1.0);
    if(intersect){
    }
    else{
    //    Result = vec4(0.0);
    }

    FragColor = Result;//mix(Result, Debug, 0.2);
}