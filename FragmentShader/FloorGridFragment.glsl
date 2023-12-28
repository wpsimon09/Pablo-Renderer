#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

float fill(float sdf){
    if(sdf <= 0.0){
        return 1.0;
    }
    else
        return 0.0;
}

float circle(vec2 pos, vec2 center, float radius){
    return length(pos-center)-radius;
 }

vec4 Float2Gray(float f) {
    return vec4(vec3(f), 1.0);
}

vec4 procedularTexture(vec2 pos)
{
    float circleSDF = circle(pos, vec2(0.5, 0.4), 0.2);
    //return Float2Gray(fill(circleSDF));
    return vec4(pos, 0.0,1.0);
}

void main(){
    vec4 texColor = procedularTexture(TexCoords);
    FragColor = texColor;
}