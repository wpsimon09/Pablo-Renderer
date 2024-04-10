#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D LUTTexture;

void main()
{
	FragColor = vec4(texture(LUTTexture, TexCoords).rgb, 1.0);
}