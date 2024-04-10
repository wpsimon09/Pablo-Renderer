#version 330

out vec4 fragmentColor;

uniform vec3 lightColor;

void main() {
	fragmentColor = vec4(lightColor, 1.0f);
}