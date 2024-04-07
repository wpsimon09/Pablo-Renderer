//
// Created by wpsimon09 on 05/02/24.
//

#include "FrameBuffer.h"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"

FrameBuffer::FrameBuffer(int SCR_WIDTH, int SCR_HEIGHT,std::shared_ptr<Shader> customShader ,std::unique_ptr<Texture2D> customColorAttachement):Renderable() {
    if(customShader == nullptr){
        this->shader = std::make_unique<Shader>("VertexShader/FrameBufferDebugVertex.glsl" , "FragmentShader/FrameBufferDebugFragment.glsl", "Texturedebug shader");
    }
    else{
        this->shader = customShader;
    }

    //FRAME BUFFER CONFIG
    glCreateFramebuffers(1, &this->ID);
    glBindFramebuffer(GL_FRAMEBUFFER, this->ID);

    // RENDER BUFFER CONFIG
    this->renderBuffer = std::make_unique<RenderBuffer>(SCR_WIDTH, SCR_HEIGHT);
    this->renderBuffer->bind();
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, this->renderBuffer->ID);
    glCheckError();

    //COLOR ATTACHMENT
    if(customColorAttachement == nullptr){
        this->colorAttachment = std::make_unique<Texture2D>(SCR_WIDTH, SCR_HEIGHT, GL_RGBA16F);
    }
    else{
        this->colorAttachment = std::move(customColorAttachement);
    }
    this->colorAttachment->bind();
    this->colorAttachment->setSamplerID(0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this->colorAttachment->ID, 0);

    //RENDERBUFFER SCREEN-SPACE QUAD CONFIG
    this->objectGeometry = std::make_unique<ScreenSpaceQuadGeometry>();
    this->objectMaterial = std::make_unique<BasicMaterialTextured>(this->shader,*this->colorAttachment);

    this->checkFrameBufferCompleteness();

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

std::shared_ptr<Texture2D> FrameBuffer::getRenderedResult(){
    return this->colorAttachment;
}

void FrameBuffer::dispalyOnScreen() {
    glViewport(0, 0, width, height);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    this->objectMaterial->configureShader();
    this->objectMaterial->shader->setVec2("mouseFocusPoint",GLFWHelper::getPointerPosition(true));
    this->objectGeometry->render();
}

void FrameBuffer::drawInsideSelf() {
    glViewport(0, 0, width, height);
    this->bind();
    glClearColor(0.03f, 0.03f, 0.03f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    this->objectMaterial->configureShader();
    this->objectGeometry->render();
}

void FrameBuffer::setShader(std::unique_ptr<Shader> shader) {
    this->shader = std::move(shader);
    this->objectMaterial->shader = std::move(shader);
}

FrameBuffer::FrameBuffer(FrameBuffer &&other):ID(other.ID), colorAttachment(std::move(other.colorAttachment)), renderBuffer(std::move(other.renderBuffer)), width(other.width), height(other.height), shader(std::move(other).shader) {

}

FrameBuffer &FrameBuffer::operator=(FrameBuffer &&other) noexcept {
    if(this != &other){
        std::swap(ID, other.ID);
        std::swap(colorAttachment, other.colorAttachment);
        std::swap(shader, other.shader);
        std::swap(renderBuffer, other.renderBuffer);
    }
    return *this;
}

void FrameBuffer::changeFilteringMethod(GLenum mag, GLenum min) {
    this->colorAttachment->changeFilteringMethod(mag, min);
}

void FrameBuffer::setColorAttachment(std::shared_ptr<Texture2D> colorAttachment) {
    this->colorAttachment = std::move(colorAttachment);
    this->objectMaterial = std::make_shared<BasicMaterialTextured>(this->shader, *std::move(this->colorAttachment));
}

void FrameBuffer::makeDepthOnly(std::shared_ptr<Texture2D> depthMapTexture) {
    if(depthMapTexture == nullptr){
        this->colorAttachment = std::make_shared<Texture2D>(this->width, this->height, GL_DEPTH_COMPONENT);
    }
    else{
        this->colorAttachment = std::move(depthMapTexture);
    }

    this->bind();

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, this->colorAttachment->ID, 0);
    glCheckError();

    //disable color buffer
    glDrawBuffer(GL_NONE);
    glCheckError();

    glReadBuffer(GL_NONE);
    glCheckError();

    this->objectMaterial = std::make_shared<BasicMaterialTextured>(this->shader, *this->colorAttachment);

    this->checkFrameBufferCompleteness();

    this->unbind();

    this->isDepthOnly = true;
}

void FrameBuffer::checkFrameBufferCompleteness() {
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE){
        std::cout<<"FRAME BUFFER COMPLETE \xE2\x9C\x93 "<<std::endl;
    }
    else{
        std::cerr<<"!!!!!!! DEPTH FRAME BUFFER NOT COMPLETE !!!!!!!!"<<std::endl;
    }
}

