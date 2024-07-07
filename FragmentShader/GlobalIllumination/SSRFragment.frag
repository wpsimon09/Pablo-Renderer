#version 460

uniform sampler2D gNormal;
uniform sampler2D gPosition;

uniform mat4 Projection;

in vec2 TexCoords;

out vec4 FragColor;

float maxDistance = 15;
float resolution = 1;
int steps = 10;
float thickness = 0.3;

void main() {

    vec2 texSize = textureSize(gPosition, 0).xy;
    vec2 texCoordCalculated = gl_FragCoord.xy / texSize;

    vec4 uv = vec4(0.0);

    vec4 positionFrom = texture(gPosition, TexCoords);
    vec4 positionFromNorm = normalize(positionFrom);
    vec4 positionTo = positionFromNorm;

    if (  positionFrom.w <= 0.0 ) {FragColor = uv; return;}

    vec3 normal = normalize(texture(gNormal, TexCoords).xyz);
    vec3 reflected = normalize(reflect(positionFromNorm.xyz, normal));

    vec4 startView = vec4(positionFrom.xyz + (reflected *         0.0), 1.0);
    vec4 endView = vec4(positionFrom.xyz +   (reflected * maxDistance), 1.0);

    vec4 startFrag = Projection * startView;
    startFrag.xyz /= startFrag.w;
    startFrag.xy = startFrag.xy * 0.5 + 0.5;
    startFrag.xy *= texSize;

    vec4 endFrag = Projection * endView;
    endFrag.xyz /= endFrag.w;
    endFrag.xy = endFrag.xy * 0.5 + 0.5;
    endFrag.xy *= texSize;

    vec2 frag = startFrag.xy;
    uv.xy = frag / texSize;

    float deltaX = endFrag.x - startFrag.x;
    float deltaY = endFrag.y - startFrag.y;

    float useX = abs(deltaX) >= abs(deltaY) ? 1.0 : 0.0;
    float delta = mix(abs(deltaY), abs(deltaX), useX) * clamp(resolution, 0.0, 1.0);

    vec2 increment = vec2(deltaX, deltaY) / max(delta, 0.001);

    float search0 = 0.0;
    float search1 = 0.0;

    float viewDistance = startView.y;
    float depth = thickness;

    int hit0 = 0;
    int hit1 = 0;

    int maxIterations = min(int(delta), 380);

    for(int i = 0; i < (maxIterations); ++i) {
        frag += increment;
        uv.xy = frag / texSize;
        positionTo = texture(gPosition, uv.xy);

        search1 = mix((frag.y - startFrag.y) / deltaY, (frag.x - startFrag.x) / deltaX, useX);
        viewDistance = (startView.y * endView.y) / mix(endView.y, startView.y, search1);
        depth = viewDistance - positionTo.y;

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
        positionTo = texture(gPosition, uv.xy);

        viewDistance = (startView.y * endView.y) / mix(endView.y, startView.y, search1);
        depth = viewDistance - positionTo.y;

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
    (1.0 - max(dot(-positionFromNorm.xyz, reflected), 0.0)) *
    (1.0 - clamp(depth / thickness, 0.0, 1.0)) *
    (1.0 - clamp(length(positionTo - positionFrom) / maxDistance, 0.0, 1.0)) *
    (uv.x < 0.0 || uv.x > 1.0 ? 0.0 : 1.0) *
    (uv.y < 0.0 || uv.y > 1.0 ? 0.0 : 1.0);

    visibility = clamp(visibility, 0.0, 1.0);
    uv.ba = vec2(visibility);
    float alpha = clamp(uv.b, 0, 1);

    FragColor = uv;

    //FragColor = vec4(normalize(delta);
    // Debug output to visualize different aspects
    // FragColor = texture(gColourShininess, TexCoords);
     //FragColor = vec4(texture(gColourShininess , TexCoords).rgb, 1.0);
    // FragColor = vec4(normalize(positionFrom), 1.0);
    // FragColor = vec4(0.0, 0.0, 0.2, 1.0);
}
