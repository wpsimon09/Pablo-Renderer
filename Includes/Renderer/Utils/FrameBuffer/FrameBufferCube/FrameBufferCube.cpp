//
// Created by wpsimon09 on 15/02/24.
//

#include "FrameBufferCube.h"
#include "Debug/DebugLogger.h"

#include <utility>

glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
glm::mat4 captureViews[] =
        {
                glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
                glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
                glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
                glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
                glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
                glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
        };

FrameBufferCube::FrameBufferCube(int width, int height, std::shared_ptr<Shader> shader, unsigned int mipLevels) {
    // SHADER
    this->shader = std::move(shader);

    // CUBE COLOR ATTACHMENT
    this->colorAttachmentCube = std::make_shared<Texture3D>(width, height, GL_RGBA32F);

    // FRAME BUFFER CREATING
    glGenFramebuffers(1,&this->ID);
    glCheckError();
    glBindFramebuffer(GL_FRAMEBUFFER, this->ID);
    glCheckError();
    // RENDER BUFFER CREATION
    this->renderBuffer = std::make_unique<RenderBuffer>(width, height);
    this->renderBuffer->bind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->renderBuffer->ID);
    glCheckError();
    // MIP LEVELS
    this->mipLevels = mipLevels;

    // CUBE GEOMETRY
    this->geometry = std::make_unique<CubeGeometry>();

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE){
        std::cout<<"CUBE FRAME BUFFER COMPLETE \xE2\x9C\x93 "<<std::endl;
    }
    else{
        std::cerr<<"!!!!!!! FRAME BUFFER NOT COMPLETE !!!!!!!!"<<std::endl;
    }

    this->width = width;
    this->height = height;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


std::shared_ptr<Texture3D> FrameBufferCube::renderToSelf(TextureBase input,unsigned int mipLevel) {
    ShaderHelper::setTextureToShader(shader, input, "envMap");
    glViewport(0, 0, width, height);
    this->bind();
    for (int i = 0; i < 6; ++i) {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                               colorAttachmentCube->ID, mipLevel);
        glCheckError();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glCheckError();
        ShaderHelper::setTransfomrationMatrices(shader, glm::mat4(1.0), captureViews[i], captureProjection);
        this->geometry->render();
    }
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

    this->unbind();
    return std::move(colorAttachmentCube);
}
//-------------
// C++ RULE 3/5
//-------------

FrameBufferCube::FrameBufferCube(FrameBufferCube &&other) noexcept : ID(other.ID),mipLevels(other.mipLevels), colorAttachmentCube(std::move(other.colorAttachmentCube)), shader(std::move(other.shader)), renderBuffer(std::move(other.renderBuffer)), geometry(std::move(other.geometry)) {

}

FrameBufferCube &FrameBufferCube::operator=(FrameBufferCube &&other) noexcept {
    if(this != &other){
        glDeleteFramebuffers(1, &this->ID);
        std::swap(ID, other.ID);
        std::swap(mipLevels, other.mipLevels);
        std::swap(shader, other.shader);
        std::swap(renderBuffer, other.renderBuffer);
        std::swap(geometry, other.geometry);

        other.ID = 0;
    }
    return *this;
}


void FrameBufferCube::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glCheckError();
}

void FrameBufferCube::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, this->ID);
    glCheckError();
}


