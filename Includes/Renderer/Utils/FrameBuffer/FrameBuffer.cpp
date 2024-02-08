//
// Created by wpsimon09 on 05/02/24.
//

#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(int SCR_WIDTH, int SCR_HEIGHT):Renderable() {
    this->shader = new Shader("VertexShader/FrameBufferDebugVertex.glsl" , "FragmentShader/FrameBufferDebugFragment.glsl", "Texturedebug shader");

    //FRAME BUFFER CONFIG
    glGenFramebuffers(1, &this->ID);
    glBindFramebuffer(GL_FRAMEBUFFER, this->ID);

    // RENDER BUFFER CONFIG
    this->renderBuffer = new RenderBuffer(SCR_WIDTH, SCR_HEIGHT);
    this->renderBuffer->bind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->renderBuffer->ID);

    //COLOR ATTACHMENT
    this->colorAttachment = new Texture2D(SCR_WIDTH, SCR_HEIGHT, GL_RGBA16F,GL_RGBA, GL_FLOAT);
    this->colorAttachment->bind();
    this->colorAttachment->setSamplerID(0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colorAttachment->ID, 0);

    //RENDERBUFFER SCREEN-SPACE QUAD CONFIG
    this->objectGeometry = new ScreenSpaceQuadGeometry();
    this->objectMaterial = new BasicMaterialTextured(this->shader,this->colorAttachment);
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE){
        std::cout<<"FRAME BUFFER COMPLETE \xE2\x9C\x93 "<<std::endl;
    }
    else{
        std::cerr<<"!!!!!!! FRAME BUFFER NOT COMPLETE !!!!!!!!"<<std::endl;
    }

    this->width = SCR_WIDTH;
    this->height = SCR_HEIGHT;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
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

void FrameBuffer::dispalyOnScreen() {
    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    this->objectMaterial->configureShader();
    this->objectGeometry->render();
}

void FrameBuffer::drawInsideSelf() {
    glViewport(0, 0, width, height);
    this->bind();
    this->objectMaterial->configureShader();
    this->objectGeometry->render();
}

void FrameBuffer::setShader(Shader *shader) {
    this->shader = shader;
}
