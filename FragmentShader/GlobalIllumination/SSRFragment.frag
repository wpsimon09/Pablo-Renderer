#version 460

uniform sampler2D gNormal;
uniform sampler2D gPosition;
uniform sampler2D gColourShininess;

uniform mat4 projection;

//controlls the length of the reflected (around Nrmal) RAY
float maxDistance = 15;

// range 0-1, how many fragments are skipped while marching the ray, if this is 1 all fragments are evaluated
// this is used in the "first pass" to determine if the ray is hit or not
float resolution = 0.3;

//ammoount of steps taken while marching along ray direction
// this is reinfinment pass
int steps = 10;

// calculations are not allways precise this allows for some error margin
float thikness = 0.5;


void main() {

}