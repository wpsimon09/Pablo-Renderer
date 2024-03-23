#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D FragmentColor;

uniform vec2 mouseFocusPoint;

float redOffset   =  0.009;
float greenOffset =  0.006;
float blueOffset  = -0.006;


void main(){
    vec3 color = texture(FragmentColor, TexCoords).rgb;

    vec2 texSize = textureSize(FragmentColor, 0).xy;
    vec2 texCoord = gl_FragCoord.xy / texSize;

    vec2 direction =  texCoord- mouseFocusPoint;

    //color = pow(color,vec3(1.0/1.2));
    //FragColor = vec4(color,1.0);

    FragColor.r  = texture(FragmentColor, texCoord + (direction * vec2(redOffset  ))).r;
    FragColor.g  = texture(FragmentColor, texCoord + (direction * vec2(greenOffset))).g;
    FragColor.ba = texture(FragmentColor, texCoord + (direction * vec2(blueOffset ))).ba;

}