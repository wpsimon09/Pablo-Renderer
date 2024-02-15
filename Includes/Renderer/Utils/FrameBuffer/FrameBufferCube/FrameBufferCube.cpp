//
// Created by wpsimon09 on 15/02/24.
//

#include "FrameBufferCube.h"

#include <utility>

FrameBufferCube::FrameBufferCube(int width, int height, TextureBase input, std::string inputShaderName,Shader *shader, unsigned int mipLevels): FrameBuffer(width, height), colorAttachmentCube(  width, height, GL_RGBA32F) {
    this->colorAttachmentCube.bind();
    this->colorAttachmentCube.setSamplerID(0);
    this->colorAttachmentCube.unbind();

    this->shader = shader;

    this->objectGeometry = new CubeGeometry();
    this->objectMaterial = new BasicMaterialTextured(shader,std::move(input), std::move(inputShaderName));
}

void FrameBufferCube::drawInsideSelf() {
    this->bind();
    for (int i = 0; i <6 ; ++i) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X +i, this->colorAttachmentCube.ID, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        this->objectMaterial->configureShader();
        ShaderHelper::setTransfomrationMatrices(this->shader,glm::mat4(0), captureViews[i], captureProjection);
        this->objectGeometry->render();
    }
}
