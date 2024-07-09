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

in vec2 TexCoords;

out vec4 FragColor;

const float step = 0.2;
const float minRayStep = 0.1;
const float maxSteps = 20;
const int numBinarySearchSteps = 100;
const float reflectionSpecularFalloffExponent = 1.2;

float Metallic;

#define Scale vec3(.8, .8, .8)
#define K 19.19

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}

vec3 PositionFromDepth(float depth) {
    float z = depth * 2.0 - 1.0;

    vec4 clipSpacePosition = vec4(TexCoords * 2.0 - 1.0, z, 1.0);
    vec4 viewSpacePosition = invProjection * clipSpacePosition;

    // Perspective division
    viewSpacePosition.xyz /= viewSpacePosition.w;

    return viewSpacePosition.xyz;
}


vec3 hash(vec3 a)
{
    a = fract(a * Scale);
    a += dot(a, a.yxz + K);
    return fract((a.xxy + a.yxx)*a.zyx);
}

vec3 BinarySearch(inout vec3 dir, inout vec3 hitCoord, inout float dDepth){
    float depth;

    vec4 projectedCoord;

    for(int i = 0; i < numBinarySearchSteps; i++)
    {

        projectedCoord = Projection * vec4(hitCoord, 1.0);
        projectedCoord.xy /= projectedCoord.w;
        projectedCoord.xy = projectedCoord.xy * 0.5 + 0.5;

        depth = texture(gDepth, projectedCoord.xy).r;


        dDepth = hitCoord.z - depth;

        dir *= 0.2;
        if(dDepth > 0.0){
            hitCoord *= dir;
        }
        else{
            hitCoord /= dir;
        }
    }

    projectedCoord = Projection * vec4(hitCoord, 1.0);
    projectedCoord.xy /= projectedCoord.w;
    projectedCoord.xy = projectedCoord.xy * 0.5 + 0.5;

    return vec3(projectedCoord.xy, depth);
}

vec4 RayMarch(vec3 dir,inout vec3 hitCoord, out float dDepth){
    dir *= step;

    float depth;
    int steps = 0;
    vec4 projectedCoord;

    for(int i = 0; i<maxSteps; i++){
        hitCoord +=dir;

        projectedCoord  = Projection * vec4(hitCoord, 1.0);
        projectedCoord.xy /= projectedCoord.w;
        projectedCoord.xy = projectedCoord.xy * 0.5 + 0.5;

        depth = texture(gDepth, projectedCoord.xy).r;
        if(depth >1000.0)
            continue;
        dDepth = hitCoord.z - depth;

        if ((dir.z - dDepth) < 0.2) {
            vec3 newCoord = hitCoord;
            float newDepth;
            hitCoord = BinarySearch(dir, newCoord, newDepth);
            dDepth = hitCoord.z - newDepth;
            return vec4(hitCoord, 1.0);
        }

        steps++;
    }

    return vec4(projectedCoord.xy, depth, 0.0);
}


void main() {
    vec4 colourShininess = texture(gColourShininess, TexCoords);
    vec4 N = normalize(texture(gNormal, TexCoords));

    vec2 MetalicRougness;

    //rougness
    MetalicRougness.r = colourShininess.a;

    //metalness
    MetalicRougness.g = N.a;

    vec3 viewNormal = vec3(normalize(vec4(N.rgb,1.0)) * invView );
    vec3 viewPos = PositionFromDepth(texture(gDepth, TexCoords).r);
    vec3 albedo = texture(gRenderedScene, TexCoords).rgb;

    float spec = MetalicRougness.r;

    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, MetalicRougness.g);
    vec3 Fresnel = fresnelSchlick(max(dot(normalize(viewNormal), normalize(viewPos)), 0.0), F0);

    vec3 R = normalize(reflect(normalize(viewPos), normalize(viewNormal)));

    vec3 hitPos = viewPos;
    float dDepth;

    vec3 wp = vec3(vec4(viewPos, 1.0) * invProjection);
    vec3 jitt = mix(vec3(0.0), vec3(hash(wp)), spec);
    vec4 coords = RayMarch(vec3( jitt * R ), hitPos, dDepth);
    vec4 coords2 = RayMarch(vec3( R), hitPos, dDepth);

    coords = mix(coords , coords2,0.2);

    vec2 dCoords = smoothstep(0.1, 0.9, abs(vec2(0.5, 0.5) - coords.xy));
    float screenEdgeFactor = clamp(1.0 - (dCoords.x + dCoords.y), 0.0,1.0);

    float ReflectionMultiplier = pow(MetalicRougness.g, reflectionSpecularFalloffExponent) * screenEdgeFactor  * -R.z;


    vec3 SSR = texture(gRenderedScene, coords.xy).rgb * ReflectionMultiplier * Fresnel;

    FragColor = vec4(SSR,1.0   );
}