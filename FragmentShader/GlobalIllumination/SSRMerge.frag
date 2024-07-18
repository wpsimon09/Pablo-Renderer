#version 460


in vec2 TexCoords;

uniform sampler2D ssr;
uniform sampler2D renderedScene;
uniform sampler2D gColourShininess;

out vec4 FragColor;

void main() {
    vec4 ssr =   texture(ssr, TexCoords);
    vec2 reflectedUV = ssr.xy;
    vec3 reflectedColour = texture(gColourShininess, reflectedUV).rgb;

    vec4 scene = texture(renderedScene, TexCoords);

    FragColor = vec4(scene.rgb,1.0) ;
    FragColor.rgb += reflectedColour;
    //FragColor = vec4(reflectedUV,0.0, 1.0);
}