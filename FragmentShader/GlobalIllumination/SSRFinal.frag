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

in vec2 TexCoords;

out vec4 FragColor;


vec3 BinarySerach(in vec3 RaySample, in vec3 PreviousRaySample){
    vec3 MinRaySample = PreviousRaySample;
    vec3 MaxRaySample = RaySample;
    vec3 MidRaySample;

    for(int i=0; i< MaxBinarySearchSteps; i++){
        MidRaySample = mix(MinRaySample, MaxRaySample, MidRaySampleWeight);
        float ZBufferVal = texture(gDepth, MidRaySample.xy).r;

        if(MidRaySample.z > ZBufferVal){
            MaxRaySample = MidRaySample;
        }else{
            MinRaySample = MidRaySample;
        }
    }

    return MidRaySample;
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
        vec3 RaySample = (RayStepIndex * MaxMarchStep) * ScreenSpaceReflectionVec + ScreenSpacePosition;

        float ZBufferVal = texture(gDepth, RaySample.xy).r;

        if(RaySample.z > ZBufferVal){
            RaySample.y = 1 - RaySample.y;
            RaySample = BinarySerach(RaySample, PrevRaySample);
            ReflectionColor = texture(gColourShininess, RaySample.xy).rbg;

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
    vec2 NDCPos = PixelUV * 2.0 - 2.0;

    // depth
    float DeviceZ = texture(gDepth, TexCoords).r;

    // position of the fragment in world
    vec4 WorldPosition4 = invProjection * invView * vec4(NDCPos, DeviceZ,0);
    vec3 WorldPosition = WorldPosition4.xyz/WorldPosition4.w;

    // vector from camera to the target fragment

    vec3 CameraVector = normalize(WorldPosition + cameraPosition);

    //normal vector in world space in 0.0
    vec3 WorldNormal = normalize(texture(gNormal, TexCoords).xyz * 2.0 - 1.0);

    vec4 ScreenSpacePos = vec4(PixelUV, DeviceZ, 1.0f);

    vec3 ReflectionVector = reflect(normalize(CameraVector), normalize(WorldNormal.xyz));

    vec4 PointAlongReflectionVec = vec4(ReflectionVecScale * ReflectionVector + WorldPosition,1.0);
    vec4 ScreenSpaceReflectionPoint = Projection * View * PointAlongReflectionVec;
    ScreenSpaceReflectionPoint /=ScreenSpaceReflectionPoint.w;
    ScreenSpaceReflectionPoint.xy = ScreenSpaceReflectionPoint.xy * vec2(0.5, -0.5) + vec2(0.5, 0.5);

    vec3 ScreenSpaceReflectionVec = normalize(ScreenSpaceReflectionPoint.xyz - ScreenSpacePos.xyz);

    vec3 OutReflectionColor = vec3(0.0);

    bool intersect = RayMarch(ScreenSpaceReflectionVec, ScreenSpacePos.xyz, OutReflectionColor);


    if(intersect){
        FragColor = vec4(OutReflectionColor,1.0);
    }
    else{
        FragColor = vec4(0.0);
    }
   //FragColor = vec4(WorldPosition,1.0);
}
