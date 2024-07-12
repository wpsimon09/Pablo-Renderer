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

    //convert from 0,1 to -1,1 aka from pixel space to screen space
    vec2 NDCPos = vec2(2.0f, 2.0f)*PixelUV + vec2(-1.0f, 1.0f);

    // depth
    float DeviceZ = texture(gDepth, TexCoords).r;

    // position of the fragment in world
    vec3 WorldPosition = vec3(vec4(NDCPos, DeviceZ,0) *invProjection);

    // vector from camera to the target fragment
    vec3 CameraVector = normalize(WorldPosition - cameraPosition);

    //normal vector in world space in 0.0
    vec4 WorldNormal = texture(gNormal) * vec4(2.0,2.0,2.0,1) - vec4(1.0,1.0,1.0,0.0);
    WorldNormal = normalize(WorldNormal);
    
    vec4 ScreenSpacePos = vec4(PixelUV, DeviceZ, 1.0f);

    vec3 ReflectionVector = normalize(reflect(normalize(CameraVector), normalize(WorldNormal.xyz)));

    



    FragColor = vec4(0.0);

}