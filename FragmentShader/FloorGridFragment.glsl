#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform float numOfDivisions;

float unionSDF(float sdf0, float sdf1) {
    return min(sdf0, sdf1);
}

float differenceSDF(float sdf0, float sdf1) {
    return max(sdf0, -sdf1);
}

float intersectionSDF(float sdf0, float sdf1) {
    return max(sdf0, sdf1);
}


vec4 Float2Gray(float f){

    return vec4(vec3(f), 1.0);
}

float fill(float sdf){
    return clamp(0.5 - sdf/fwidth(sdf), 0.0, 1.0);
}

float stroke(float sdf, float strokeWidt){
    return fill(abs(sdf)-strokeWidt);
}

float circle(vec2 pos, vec2 center, float radius){
    return length(pos-center)-radius;
 }

float stripes(float x, float divisions){
    return (abs(fract(x * 0.5 * divisions) - 0.5) * 2.0 - 0.5)/divisions;
}

float grid(vec2 pos, float divisions){
    float part1 = differenceSDF(stripes(pos.x, divisions), stripes(pos.y, divisions));
    vec2 posTrans = pos + 1.0 / divisions;
    float part2 = differenceSDF(stripes(posTrans.x, divisions), stripes(posTrans.y, divisions));
    return stroke((unionSDF(part1, part2)),0.001);
}

vec4 procedularTexture(vec2 pos)
{
    float circleSDF = circle(pos, vec2(0.5, 0.5), 0.2);
    float gridSDF = grid(pos,numOfDivisions);
    float alpha = 1.0 - fill(gridSDF);
    return vec4(Float2Gray(gridSDF).xyz, alpha);
    //return vec4(pos, 0.0,1.0);
}

void main(){
    vec4 texColor = procedularTexture(TexCoords);


    FragColor = texColor;
}