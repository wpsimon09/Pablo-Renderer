#version 460


in vec2 TexCoords;

uniform sampler2D ssr;
uniform sampler2D renderedScene;
uniform sampler2D gColourShininess;
uniform sampler2D gMetalnessRougness;

out vec4 FragColor;

precision highp float;

void main() {
    vec4 ssr =   texture(ssr, TexCoords);
    vec2 reflectedUV = ssr.xy;
    vec3 reflectedColour = texture(gColourShininess, reflectedUV).rgb;
    vec4 scene = textureLod(renderedScene, TexCoords,0);

    FragColor = vec4(mix(reflectedColour,scene.rgb ,0.5) ,1.0);
}