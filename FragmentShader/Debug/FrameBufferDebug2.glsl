#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D FragmentColor;

const float offset = 1.0/200.0;

void main(){
    //FragColor = vec4(1.0f, 0.0f, 0.0f,1.0f);

    vec2 offsets[9] = vec2[](
    vec2(-offset, offset), // top-left
    vec2( 0.0f, offset), // top-center
    vec2( offset, offset), // top-right
    vec2(-offset, 0.0f), // center-left
    vec2( 0.0f, 0.0f), // center-center
    vec2( offset, 0.0f), // center-right
    vec2(-offset, -offset), // bottom-left
    vec2( 0.0f, -offset), // bottom-center
    vec2( offset, -offset) // bottom-right
    );

    float kernel[9] = float[](
    -1, -1, -1,

    -1, 10, -1,

    -1, -1, -1
    );

    //texels to apply efect on
    vec3 sampleTex[9];

    //get all of the texels
    for(int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(FragmentColor, TexCoords.st +
        offsets[i]).rgb);
    }
    vec3 col = vec3(0.0);

    //apply effect using kernel
    for(int i = 0; i < 9; i++)
        col += sampleTex[i] * kernel[i];

    FragColor = vec4(col, 1.0);
}