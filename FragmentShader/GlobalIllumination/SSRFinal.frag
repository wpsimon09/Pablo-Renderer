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

in vec2 TexCoords;

out vec4 FragColor;


bool RayMarch(
        vec3 ScreenSpaceReflectionVec,
        vec3 ScreenSpacePosition,
        out vec3 ReflectionColor
){
    for(int RayStepIndex = 0; RayStepIndex < MaxSamplerCount; RayStepIndex++){
        vec3 RaySample = (RayStepIndex * MaxMarchStep) * ScreenSpaceReflectionVec + ScreenSpacePosition;
        float ZBufferVal = texture(gDepth, RaySample.xy).r;

        if(RaySample.z > ZBufferVal){
            ReflectionColor = texture(gColourShininess, RaySample.xy).rbg;
            return true;
        }

    }
    return false;
}

void main() {
    vec2 depthBufferSize = textureSize(gDepth, 0);

    vec2 PixelUV = TexCoords;

    //convert from 0,1 to -1,1 aka from pixel space to screen space
    vec2 NDCPos = vec2(2.0f, -2.0f)*PixelUV + vec2(-1.0f, 1.0f);

    // depth
    float DeviceZ = texture(gDepth, TexCoords).r;

    // position of the fragment in world
    vec3 WorldPosition = vec3(invProjection * vec4(NDCPos, DeviceZ,0) );

    // vector from camera to the target fragment
    vec3 CameraVector = normalize(WorldPosition - cameraPosition);

    //normal vector in world space in 0.0
    vec4 WorldNormal = texture(gNormal, TexCoords) * vec4(2.0,2.0,2.0,1) - vec4(1.0,1.0,1.0,0.0);

    vec4 ScreenSpacePos = vec4(PixelUV, DeviceZ, 1.0f);

    vec3 ReflectionVector = reflect(normalize(CameraVector), normalize(WorldNormal.xyz));

    vec4 PointAlongReflectionVec = vec4(ReflectionVecScale * ReflectionVector + WorldPosition,1.0);
    vec4 ScreenSpaceReflectionPoint = invProjection * PointAlongReflectionVec;
    ScreenSpaceReflectionPoint /=ScreenSpaceReflectionPoint.w;
    ScreenSpaceReflectionPoint.xy = ScreenSpaceReflectionPoint.xy * vec2(0.5, -0.5) + vec2(0.5, 0.5);

    vec3 ScreenSpaceReflectionVec = normalize(ScreenSpaceReflectionPoint.xyz - ScreenSpacePos.xyz);

    vec3 OutReflectionColor = vec3(0.0);

    bool intersect = RayMarch(ScreenSpaceReflectionVec, ScreenSpacePos.xyz, OutReflectionColor);


    //FragColor = vec4(texture(WorldNormal,TexCoords));
    if(intersect){
        FragColor = vec4(OutReflectionColor,1.0);
    }
    else{
        FragColor = vec4(0.0);
    }
}