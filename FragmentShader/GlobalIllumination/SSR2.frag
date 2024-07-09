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

float maxDistance = 15;
float resolution  = 0.3;
int   steps       = 10;
float thickness   = 0.5;


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

void main() {
    vec2 texSize = textureSize(gColourShininess, 0);
    vec4 colourShininess = texture(gColourShininess, TexCoords);
    vec4 N = normalize(texture(gNormal, TexCoords));

    vec2 MetalicRougness;

    //rougness
    MetalicRougness.r = colourShininess.a;

    //metalness
    MetalicRougness.g = N.a;

    vec3 viewNormal = vec3(normalize(vec4(N.rgb,1.0)) * invProjection );
    vec3 viewPos = PositionFromDepth(texture(gDepth, TexCoords).r);
    vec3 albedo = texture(gRenderedScene, TexCoords).rgb;


    float spec = MetalicRougness.r;

    vec3 F0 = vec3(0.04);
    F0 = mix(F0, albedo, MetalicRougness.g);
    vec3 Fresnel = fresnelSchlick(max(dot(normalize(viewNormal), normalize(viewPos)), 0.0), F0);

    vec3 R = normalize(reflect(normalize(viewPos), normalize(viewNormal)));

    vec4 startView = vec4(viewPos.xyz + (R*0),1);
    vec4 endView = vec4(viewPos.xyz + (R*maxDistance),1);

    vec4 positionTo = vec4(0.0);
    vec4 positionFrom = vec4(0.0);

    vec4 startFrag =  startView;
    startFrag.xyz /= startFrag.w;

    startFrag.xy = startFrag.xy * 0.5 + 0.5;

    startFrag.xy *= texSize;

    vec4 endFrag  = endView;
    endFrag.xyz /= endFrag.w;
    endFrag.xy *= endFrag.xy * 0.5 + 0.5;
    endFrag.xy *= texSize;

    vec2 frag = startFrag.xy;
    float deltaX = endFrag.x - startFrag.x;
    float deltaY = endFrag.y - startFrag.y;


    float useX      = abs(deltaX) >= abs(deltaY) ? 1 : 0;
    float delta     = mix(abs(deltaY), abs(deltaX), useX) * clamp(resolution, 0, 1);

    vec2  increment = vec2(deltaX, deltaY) / max(delta, 0.001);

    float search0 = 0;
    float search1 = 0;

    int hit0 = 0;
    int hit1 = 0;


    float viewDistance = startView.y;
    float depth        = thickness;

    vec4 uv = vec4(0.0);
    int maxIterations = min(int(delta), 200);

    for (int i = 0; i < maxIterations; ++i) {
        frag += increment;
        uv.xy = frag / texSize;

        depth = viewDistance - texture(gDepth, uv.xy).r;
        positionTo.xyz = PositionFromDepth(depth);

        if(depth > 0.0 && depth < thickness) {
            hit0 = 1;
            break;
        } else {
            search0 = search1;
        }
    }

    search1 = search0 + ((search1 - search0) / 2.0);
    steps *= hit0;


     maxIterations = min(int(steps), 400);

    for(int i = 0; i < maxIterations; ++i) {
        frag = mix(startFrag.xy, endFrag.xy, search1);
        uv.xy = frag / texSize;


        depth = viewDistance - texture(gDepth, uv.xy).r;

        positionTo.xyz = PositionFromDepth(depth);

        if(depth > 0.0 && depth < thickness) {
            hit1 = 1;
            search1 = search0 + ((search1 - search0) / 2.0);
        } else {
            float temp = search1;
            search1 = search1 + ((search1 - search0) / 2.0);
            search0 = temp;
        }
    }

    float visibility = hit1 * positionTo.w *
    (1.0 - max(dot(-normalize(positionFrom.xyz), R), 0.0)) *
    (1.0 - clamp(depth / thickness, 0.0, 1.0)) *
    (1.0 - clamp(length(positionTo - positionFrom) / maxDistance, 0.0, 1.0)) *
    (uv.x < 0.0 || uv.x > 1.0 ? 0.0 : 1.0) *
    (uv.y < 0.0 || uv.y > 1.0 ? 0.0 : 1.0);

    visibility = clamp(visibility, 0.0, 1.0);
    uv.ba = vec2(visibility);
    float alpha = clamp(uv.b, 0, 1);

    FragColor = uv;


    vec3 SSR = texture(gRenderedScene, uv.xy).rgb * Fresnel;

    FragColor = vec4(SSR,1.0   );
}