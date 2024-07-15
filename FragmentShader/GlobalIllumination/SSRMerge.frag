#version 460


in vec2 TexCoords;

uniform sampler2D ssr;
uniform sampler2D renderedScene;

out vec4 FragColor;

void main() {
    vec4 ssr =   texture(ssr, TexCoords);
    vec4 scene = texture(renderedScene, TexCoords);

    FragColor = vec4(mix(ssr.rgb,scene.rgb,0.5),1.0) ;
   // FragColor = vec4(ssr.rgb, 1.0);
}