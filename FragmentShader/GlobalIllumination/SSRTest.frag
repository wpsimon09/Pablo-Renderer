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



bool rayIsOutofScreen(vec2 ray) {
    return (ray.x > 1 || ray.y > 1 || ray.x < 0 || ray.y < 0) ? true : false;
}

vec3 TraceRay(vec3 rayPos, vec3 dir, int iterationCount) {
    float sampleDepth;
    vec3 hitColor = vec3(0);
    bool hit = false;

    for (int i = 0; i < iterationCount; i++) {
        rayPos += dir;
        if (rayIsOutofScreen(rayPos.xy)) {
            break;
        }

        sampleDepth = texture(gDepth, rayPos.xy).r;
        float depthDif = rayPos.z - sampleDepth;
        if (depthDif >= 0 && depthDif < 0.00001) { //we have a hit
               hit = true;
               hitColor = texture(gColourShininess, rayPos.xy).rgb;
               break;
        }
    }
    return hitColor;
}

void main() {
    float maxRayDistance = 100.0f;

    //View Space ray calculation
    vec3 pixelPositionTexture;
    pixelPositionTexture.xy = TexCoords;

    float pixelDepth = texture(gDepth, pixelPositionTexture.xy).r;    // 0< <1
    pixelPositionTexture.z = pixelDepth;

    vec3 normalView =vec3(vec4(texture(gNormal, pixelPositionTexture.xy).rgb,1.0) * View);

    vec4 positionView = invProjection * vec4(pixelPositionTexture * 2 - vec3(1), 1);
    positionView /= positionView.w;

    vec3 reflectionView = normalize(reflect(positionView.xyz, normalView));
    if (reflectionView.z > 0) {
        FragColor = vec4(0, 0, 0, 1);
        return;
    }

    vec3 rayEndPositionView = positionView.xyz + reflectionView * maxRayDistance;


    //Texture Space ray calculation
    vec4 rayEndPositionTexture = Projection * vec4(rayEndPositionView, 1);
    rayEndPositionTexture /= rayEndPositionTexture.w;
    rayEndPositionTexture.xyz = (rayEndPositionTexture.xyz + vec3(1)) / 2.0f;

    vec3 rayDirectionTexture = rayEndPositionTexture.xyz - pixelPositionTexture;

    vec2 size = textureSize(gDepth, 0);

    ivec2 screenSpaceStartPosition = ivec2(pixelPositionTexture.x * size.x, pixelPositionTexture.y * size.y);
    ivec2 screenSpaceEndPosition = ivec2(rayEndPositionTexture.x * size.x, rayEndPositionTexture.y * size.y);

    ivec2 screenSpaceDistance = screenSpaceEndPosition - screenSpaceStartPosition;
    int screenSpaceMaxDistance = max(abs(screenSpaceDistance.x), abs(screenSpaceDistance.y)) / 2;
    rayDirectionTexture /= max(screenSpaceMaxDistance, 0.001f);


    //trace the ray
    vec3 outColor = TraceRay(pixelPositionTexture, rayDirectionTexture, screenSpaceMaxDistance);
    FragColor = vec4(outColor, 1);
}