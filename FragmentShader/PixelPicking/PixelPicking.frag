#version 460

out vec4 FragmentColor;

uniform float objectID;

void main() {
    FragmentColor = vec4(objectID,0.0, 0.0, 1.0);
}