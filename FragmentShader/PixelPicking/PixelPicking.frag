#version 460

out vec3 FragmentColor;

uniform int objectID;

void main() {
    FragmentColor = vec3(objectID, gl_PrimitiveID+1, 0.0);
}