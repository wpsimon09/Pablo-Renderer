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

in vec2 TexCoords;

out vec4 FragColor;

float linearizeDepth(float depth){
    float z = depth * 2.0 - 1.0; // back to NDC
    return (2.0 * NearPlane * FarPlane) / (FarPlane + NearPlane - depth  * (FarPlane - NearPlane));
}

vec3 BinarySerach(in vec3 RaySample, in vec3 PreviousRaySample){
    vec3 MinRaySample = PreviousRaySample;
    vec3 MaxRaySample = RaySample;
    vec3 MidRaySample;

    for(int i=0; i< MaxBinarySearchSteps; i++){
        MidRaySample = mix(MinRaySample, MaxRaySample, MidRaySampleWeight);
        float ZBufferVal = texture(gDepth, MidRaySample.xy).r;
        ZBufferVal = linearizeDepth(ZBufferVal);
        if(MidRaySample.z > ZBufferVal){
            MaxRaySample = MidRaySample;
        }else{
            MinRaySample = MidRaySample;
        }
    }

    return MidRaySample ;
}

vec3 PositionFromDepth(float depth) {
    float z = depth * 2.0 - 1.0;

    vec4 clipSpacePosition = vec4(TexCoords * 2.0 - 1.0, z, 1.0);
    vec4 viewSpacePosition = invProjection * clipSpacePosition;

    // Perspective division
    viewSpacePosition.xyz /= viewSpacePosition.w;

    return viewSpacePosition.xyz;
}

bool RayMarch(
        vec3 ScreenSpaceReflectionVec,
        vec3 ScreenSpacePosition,
        out vec3 ReflectionColor
){
    vec3 PrevRaySample = (0 * MaxMarchStep) * ScreenSpaceReflectionVec + ScreenSpacePosition;;
    for(int RayStepIndex = 0; RayStepIndex < MaxSamplerCount; RayStepIndex++){
        vec3 RaySample = (RayStepIndex * -MaxMarchStep) *  ScreenSpaceReflectionVec + ScreenSpacePosition;

        float ZBufferVal = texture(gDepth, RaySample.xy).r;
        ZBufferVal = linearizeDepth(ZBufferVal);
        if(RaySample.z > ZBufferVal){

            RaySample.y = -RaySample.y;
            RaySample = BinarySerach(RaySample, PrevRaySample);

            ReflectionColor =texture(gColourShininess, PrevRaySample.xy).rbg;

            return true;
        }
        PrevRaySample = RaySample;
    }
    return false;
}



void main() {
    vec2 depthBufferSize = textureSize(gDepth, 0);

    vec2 PixelUV = TexCoords;

    //convert from 0,1 to -1,1 aka from pixel space to screen space
    vec2 NDCPos = vec2(2.f,-2.f) * PixelUV + vec2(1.f,-1.f);;

    // depth
    float DeviceZ = texture(gDepth, TexCoords).r;
    DeviceZ = linearizeDepth(DeviceZ);

    // position of the fragment in world
    vec4 WorldPosition4 = invProjection * invView * vec4(NDCPos, DeviceZ,0);
    vec3 WorldPosition = WorldPosition4.xyz / WorldPosition4.w;

    // vector from camera to the target fragment

    vec3 CameraVector = normalize(WorldPosition + cameraPosition);

    //normal vector in world space in 0.0
    vec3 WorldNormal = normalize(texture(gNormal, TexCoords).xyz);

    vec4 ScreenSpacePos = vec4(PixelUV, DeviceZ, 1.0f);

    vec3 ReflectionVector = reflect(normalize(CameraVector), normalize(WorldNormal.xyz));

    vec4 PointAlongReflectionVec = vec4(ReflectionVecScale * ReflectionVector + WorldPosition,1.0);
    vec4 ScreenSpaceReflectionPoint = Projection * View * PointAlongReflectionVec;
    ScreenSpaceReflectionPoint.xyz /= ScreenSpaceReflectionPoint.w;
    ScreenSpaceReflectionPoint.xy = ScreenSpaceReflectionPoint.xy * vec2(0.5, -0.5) + vec2(0.5, -   0.5);;

    vec3 ScreenSpaceReflectionVec = normalize(ScreenSpaceReflectionPoint.xyz - ScreenSpacePos.xyz);

    vec3 OutReflectionColor = vec3(0.0);

    bool intersect = RayMarch(ScreenSpaceReflectionVec, ScreenSpacePos.xyz, OutReflectionColor);

    vec4 Result = vec4(0.0f);

    if(intersect){
        Result = vec4(OutReflectionColor,1.0);
    }
    else{
        Result = vec4(0.0);
    }

    vec4 Debug = vec4(vec3(DeviceZ),1.0);

    FragColor = Result;//mix(Result, Debug, 0.2);
}
