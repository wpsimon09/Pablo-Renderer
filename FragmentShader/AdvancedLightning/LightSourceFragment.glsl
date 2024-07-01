#version 330 core

layout (location = 3) out vec4 FragColor;

uniform sampler2D lightTexture;

uniform vec3 lightColor;

in vec2 TextureCoords;


void main() {

	vec4 texColor = texture(lightTexture, TextureCoords);
	if(texColor.a < 0.1)
		discard;

	FragColor = vec4(lightColor, 1.0f);
}