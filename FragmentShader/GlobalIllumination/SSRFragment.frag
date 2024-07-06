#version 460

uniform sampler2D gNormal;
uniform sampler2D gPosition;
uniform sampler2D gColourShininess;

in mat4 Pojection;

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
    vec4 positionFrom = texture(gPosition, TexCoords);

    //above but normalized
    vec4 positionFromNorm = normalize(positionFrom);

    vec4 positionTo = positionFromNorm;

    // normalized normal vector
    vec3 normal = normalize(texture(gNormal, TexCoords).xyz);

    // reflected vector
    vec3 reflected = normalize(reflect(positionFromNorm.xyz,normal));

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
    float search1 = 0;


    float viweDistance = startView.z;
    float depth = thikness;

    int hit0 = 0;
    int hit1 = 0;


    // FIRST PASS FOR RAY MARCHING
    for(int i  =0; i<delta; ++i){
        frag += increment;
        uv.xy = frag/texSize;
        positionTo = texture(gPosition, uv.xy);

        search1 = mix((frag.y - startFrag.y)/deltaY , (frag.x - startFrag.x)/deltaX, useX);

        viweDistance = (startView.y * endView.y)/mix(endView.y, startView.y, search1);

        depth = viweDistance - positionTo.y;

        if(depth > 0 && depth < thikness){
            hit0 = 1;
            break;
        }else{
            search0 = search1;
        }
    }

    search1 = search0 + ((search1 - search0)/2);

    steps *= hit0;

    for(int i = 0; i<steps; ++i){
        frag = mix(startFrag.xy, endFrag.xy, search1);
        uv.xy = frag/texSize;
        positionTo = texture(gPosition, uv.xy);

        viweDistance = (startView.y * endView.y)/mix(endView.y , startView.y, search1);

        depth = viweDistance - positionTo.y;

        if(depth > 0 && depth < thikness){
            hit1 = 1;
            search1 = search0 + ((search1 - search0)/2);
        }else{
            float temp = search1;
            search1 = search1 + ((search1- search0)/2);
            search0 = temp;
        }
    }

    float visibility =
    hit1
    * positionTo.w
    * ( 1
    - max
    ( dot(-positionFromNorm.xyz, reflected)
    , 0
    )
    )
    * ( 1
    - clamp
    ( depth / thikness
    , 0
    , 1
    )
    )
    * ( 1
    - clamp
    (   length(positionTo - positionFrom)
        / maxDistance
    , 0
    , 1
    )
    )
    * (uv.x < 0 || uv.x > 1 ? 0 : 1)
    * (uv.y < 0 || uv.y > 1 ? 0 : 1);

    visibility = clamp(visibility, 0,1);
    uv.ba = vec2(visibility);

    FragColor = texture(gColourShininess, uv.xy);
    //FragColor = vec4(texture(gColourShininess , TexCoords).rgb, 1.0);
    //FragColor = vec4(normalize(positionFrom),1.0);

    //FragColor = vec4(0.0,0.0,0.2,1.0);
}