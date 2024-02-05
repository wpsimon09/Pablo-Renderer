//
// Created by wpsimon09 on 05/02/24.
//

#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int SCR_WIDTH, int SCR_HEIGHT) {
    this->shader = new Shader("VertexShader/FrameBufferDebugVertex.glsl" , "FragmentShader/FrameBufferDebugFragment.glsl", "Texturedebug shader");

    //FRAME BUFFER CONFIG
    glGenFramebuffers(1, &this->ID);
    glGetError();
    glBindFramebuffer(GL_FRAMEBUFFER, this->ID);
    glGetError();

    // RENDER BUFFER CONFIG
    this->renderBuffer = new RenderBuffer(SCR_WIDTH, SCR_HEIGHT);
    this->renderBuffer->bind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->renderBuffer->ID);

    //COLOR ATTACHMENT
    this->colorAttachment = new Texture2D(SCR_WIDTH, SCR_HEIGHT);
    this->colorAttachment->bind();
    this->colorAttachment->setSamplerID(0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colorAttachment->ID, 0);

    //RENDERBUFFER SCREEN-SPACE QUAD CONFIG
    this->objectGeometry = new ScreenSpaceQuadGeometry();
    this->objectMaterial = new BasicMaterialTextured(this->colorAttachment);


}

void FrameBuffer::bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, this->ID);
    glGetError();
}

void FrameBuffer::unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glGetError();
}

Texture2D *FrameBuffer::getRenderedResult() {
    return this->colorAttachment;
}
