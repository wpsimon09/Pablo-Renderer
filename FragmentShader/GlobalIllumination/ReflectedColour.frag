#version 460

uniform sampler2D reflectedUVCoordinatesMap;
uniform sampler2D colourTexture;

in vec2 TexCoords;

out vec4 FragColor;

void main() {
    vec4 uv    = texture(reflectedUVCoordinatesMap,    TexCoords);
    vec4 color = texture(colourTexture, uv.xy);

    float alpha = clamp(uv.b, 0, 1);
    FragColor = vec4(mix(vec3(0), color.rgb, alpha), alpha);

    //FragColor = color;
}