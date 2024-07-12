#version 460

uniform sampler2D gNormal;
uniform sampler2D gPosition;
uniform sampler2D gColourShininess;
uniform sampler2D gRenderedScene;
uniform sampler2D gDepth;

uniform mat4 Projection;
uniform mat4 invProjection;

uniform mat4 View;
uniform mat4 invView;

uniform vec3 cameraPosition;

in vec2 TexCoords;

out vec4 FragColor;

void main() {
    vec2 depthBufferSize = textureSize(gDepth, 0);

    vec2 PixelUV = TexCoords;

    //convert from 0,1 to -1,1
    vec2 NDCPos = vec2(2.0f, 2.0f)*PixelUV + vec2(-1.0f, 1.0f);

    float DeviceZ = texture(gDepth, TexCoords).r;
    vec3 WorldPosition = vec3(vec4(NDCPos, DeviceZ,0) *invProjection);
    vec3 CameraVector = normalize(WorldPosition - cameraPosition);


    FragColor = vec4(0.0);

}