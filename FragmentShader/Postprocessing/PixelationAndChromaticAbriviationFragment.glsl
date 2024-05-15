#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D sceneResult;

uniform int pixelSize ;

void main(){
    vec4 color;

    float x =  int(gl_FragCoord.x)%pixelSize;
    float y = int (gl_FragCoord.y)%pixelSize;

    x = floor(pixelSize/2.0) -x;
    y = floor(pixelSize/2.0) - y;

    x = gl_FragCoord.x +x;
    y = gl_FragCoord.y + y;

    vec2 texSize  = textureSize(sceneResult, 0).xy;

    color = texture(sceneResult, vec2(x,y)/texSize).rgba;

    FragColor = color;
}