//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_FRAMEBUFFERCUBE_H
#define PABLO_RENDERER_FRAMEBUFFERCUBE_H

#include "Renderer/Utils/FrameBuffer/FrameBuffer.h"
#include "Renderer/Geometry/Shapes/Cube/CubeGeometry.h"
#include "Renderer/Utils/Texture/Texture3D/Texture3D.h"
#include "Renderer/Utils/ShaderHelper/ShaderHelper.h"
class FrameBufferCube:public FrameBuffer {
public:
    FrameBufferCube(int width, int height, TextureBase input, std::string inputShaderName,Shader* shader, unsigned int mipLevels);
    unsigned int mipLevels;
    Texture3D colorAttachmentCube;

    void drawInsideSelf() override;


};

glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
glm::mat4 captureViews[] = {
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
};

#endif //PABLO_RENDERER_FRAMEBUFFERCUBE_H
