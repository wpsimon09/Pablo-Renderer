#version 460


in vec2 TexCoords;

uniform sampler2D ssr;
uniform sampler2D renderedScene;

out vec4 FragColor;

void main() {
    vec4 ssr =   texture(ssr, TexCoords);
    vec4 scene = texture(renderedScene, TexCoords);

    FragColor = ssr;
}