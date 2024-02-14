#version 330 core

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLight;
}fs_in;

out vec4 FragColor;


uniform sampler2D texture_diffuse0;

void main()
{

    vec3 color = vec3(1.0);
    if (abs(gl_FragCoord.x - gl_FragCoord.y) < 0.1 || abs(gl_FragCoord.x + gl_FragCoord.y - 800) < 0.1) {
        color = vec3(1.0, 0.0,0.0);
    }
    if (abs(gl_FragCoord.x - gl_FragCoord.y - 400) < 0.1 || abs(gl_FragCoord.x + gl_FragCoord.y - 1200) < 0.1) {
        color = vec3(0.0,0.0,1.0);
    }
    FragColor = vec4(color, 0.9);
}