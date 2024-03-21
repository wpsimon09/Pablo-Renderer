#version 330 core

uniform sampler2D lightTexture;

uniform vec3 lightColor;

in vec2 TextureCoords;

out vec4 FragmentColor;

void main() {

	vec4 texColor = texture(lightTexture, TextureCoords);
	if(texColor.a < 0.1)
		discard;

	FragmentColor = vec4(lightColor, 1.0f);
}