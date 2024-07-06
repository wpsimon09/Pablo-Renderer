#version 460

uniform sampler2D gNormal;
uniform sampler2D gPosition;
uniform sampler2D gColourShininess;

uniform mat4 projection;

in vec2 TexCoords;

out vec4 FragColor;

//controlls the length of the reflected (around Nrmal) RAY
float maxDistance = 15;

// range 0-1, how many fragments are skipped while marching the ray, if this is 1 all fragments are evaluated
// this is used in the "first pass" to determine if the ray is hit or not
float resolution = 0.3;

//ammoount of steps taken while marching along ray direction
// this is reinfinment pass
int steps = 10;

// calculations are not allways precise this allows for some error margin
float thikness = 0.5;

void main() {
    vec4 uv = vec4(0.0);

    vec2 texSize  = textureSize(gPosition, 0).xy;
    vec2 texCoordCalculated = gl_FragCoord.xy / texSize;

    // vector from camera to the position of the fragmnet
    vec3 positionFrom = texture(gPosition, TexCoords).xyz;

    //above but normalized
    vec3 positionFromNorm = normalize(positionFrom.xyz);

    // normalized normal vector
    vec3 normal = normalize(texture(gNormal, TexCoords).xyz);

    // reflected vector
    vec3 reflected = normalize(reflect(positionFromNorm,normal));

    // start of the ray martching
    vec4 startView = vec4(positionFrom.xyz + (reflected * 0),        1.0);

    // end of the raymarching
    vec4 endView  = vec4(positionFrom.xyz + (reflected*maxDistance), 1.0);

    // calculate the start point in the view space
    // -------------------------------------------
    vec4 startFrag = startView;
    // translate to view space the fragment position
    startFrag = projection * startFrag;
    // preform prespective devitions
    startFrag.xyz /= startFrag.w;
    //convert screen space coordinates to UV coordinates
    startFrag.xy = startFrag.xy * 0.5 + 0.5;
    // convert from UV cooridnates to the pixel coordinates
    startFrag.xy *= texSize;

    // calculate the start point in the view space
    // -------------------------------------------
    vec4 endFrag = endView;
    endFrag = projection* endFrag;
    endFrag.xyz /= endFrag.w;
    endFrag.xy = endFrag.xy * 0.5 + 0.5;
    endFrag.xy *= texSize;

    vec2 frag = startFrag.xy;
    uv.xy = frag/texSize;

    // difference betwen begining of the ray to its end
    float deltaX = endFrag.x - startFrag.x;
    float deltaY = endFrag.y - startFrag.y;

    float useX = abs(deltaX) >= abs(deltaY) ? 1 : 0;
    float delta = mix(abs(deltaY), abs(deltaX), useX) * clamp(resolution, 0 ,1);

    vec2 increment = vec2(deltaX, deltaY) / max(delta,0.001);

    float search0 = 0;
    float serach1 = 0;

    float viweDistance = startFrag.y;
    //float depth = thikness;


    FragColor = vec4(texture(gNormal , TexCoords).rgb, 1.0);
    FragColor = vec4(normalize(positionFrom),1.0);

}