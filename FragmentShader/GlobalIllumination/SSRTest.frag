#version 460


uniform sampler2D gNormal;
uniform sampler2D gPosition;
uniform sampler2D gColourShininess;
uniform sampler2D gRenderedScene;
uniform sampler2D gDepth;
uniform sampler2D gMetalnessRougness;

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
uniform float MaxDistance;

uniform float NearPlane;
uniform float FarPlane;

in vec2 TexCoords;

out vec4 FragColor;

precision highp float;
precision highp int;

#define Scale vec3(.8, .8, .8)
#define K 19.19



bool rayIsOutofScreen(vec2 ray) {
    return (ray.x > 1|| ray.y > 1 || ray.x < 0 || ray.y < 0) ? true : false;
}

float LinearizeDepth(float depth) {
    float z = depth * 2.0 - 1.0; // Back to NDC
    return depth;
    //return (2.0 * NearPlane * FarPlane) / (FarPlane + NearPlane - z * (FarPlane - NearPlane));
}


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


bool TraceRay(vec3 RayStartingPossition, vec3 RayDirection, out vec3 ReflectedUV) {
    float sampleDepth;
    vec3 hitColor = vec3(0);
    bool hit = false;
    vec3 prevRayPos = RayStartingPossition;
    vec3 currentRayPos = RayStartingPossition;

    for (int i = 0; i < MaxSamplerCount; i++) {
        currentRayPos += RayDirection * MaxMarchStep;
        if (rayIsOutofScreen(currentRayPos.xy)) {
            break;
        }

        sampleDepth = LinearizeDepth(texture(gDepth,currentRayPos.xy).r);
        float depthDif = currentRayPos.z - sampleDepth;
        if (depthDif >= 0 && depthDif < 0.00001) { //we have a hit
               hit = true;
               currentRayPos = BinarySearch(currentRayPos, prevRayPos);

               ReflectedUV = texture(gColourShininess, currentRayPos.xy).rgb;
               return true;
        }
        prevRayPos = currentRayPos;
    }
    ReflectedUV = vec3(1.0,0.0,0.0);
    return false;
}

vec3 hash(vec3 a)
{
    a = fract(a * Scale);
    a += dot(a, a.yxz + K);
    return fract((a.xxy + a.yxx)*a.zyx);
}


void main() {
    float maxRayDistance = 100.0f;

    //View Space ray calculation
    vec3 PixelPositionTextureSpace;
    PixelPositionTextureSpace.xy = TexCoords;

    //depth of the given pixel
    float PixelDepth = texture(gDepth, PixelPositionTextureSpace.xy).r;    // 0< <1
    PixelPositionTextureSpace.z = LinearizeDepth(PixelDepth);

    vec3 NormalView =vec3(vec4(texture(gNormal, TexCoords).rgb, 1.0)*invView  );

    vec4 PositionWorldSpace = texture(gPosition, TexCoords);
    vec4 PositionViewSpace = View * PositionWorldSpace;
    vec4 ViewRay = PositionViewSpace;

    vec2 RoughnessMetalness = texture(gMetalnessRougness,TexCoords).rg;

    vec3 jitt = mix(vec3(0.0), vec3(hash(ViewRay.xyz)),RoughnessMetalness.r);

    vec3 reflectionView = normalize(reflect(ViewRay.xyz * jitt, NormalView));

    if (reflectionView.z > 0) {
        FragColor = vec4(0, 0, 0, 1);
        return;
    }


    vec3 rayEndPositionView = ViewRay.xyz + reflectionView * ReflectionVecScale;

    //Texture Space ray calculation
    vec4 rayEndPositionTexture = Projection * vec4(rayEndPositionView, 1);
    rayEndPositionTexture /= rayEndPositionTexture.w;
    rayEndPositionTexture.xyz = (rayEndPositionTexture.xyz + vec3(1)) / 2.0f;

    vec3 RayDirection = rayEndPositionTexture.xyz - PixelPositionTextureSpace;

    vec2 size = textureSize(gDepth, 0);

    vec2 ScreenSpaceStartPosition = ivec2(PixelPositionTextureSpace.x * size.x, PixelPositionTextureSpace.y * size.y);
    vec2 ScreenSpaceEndPosition = ivec2(rayEndPositionTexture.x * size.x, rayEndPositionTexture.y * size.y);

    vec2 RayLength = ScreenSpaceEndPosition - ScreenSpaceStartPosition;
    float screenSpaceMaxDistance =  max(abs(RayLength.x), abs(RayLength.y)) / MaxDistance;
    RayDirection /= max(screenSpaceMaxDistance, 0.001f);



    //trace the ray
    vec3 outColor;

    bool intersects = TraceRay(PixelPositionTextureSpace, RayDirection, outColor);
    if(intersects)
        FragColor = vec4(outColor, 1);
    else
        FragColor = vec4(0.0);
}