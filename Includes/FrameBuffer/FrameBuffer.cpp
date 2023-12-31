//
// Created by wpsimon09 on 23/12/23.
//

#include "FrameBuffer.h"


FrameBuffer::FrameBuffer() {
    glGenFramebuffers(1, &this->ID);
    glGenRenderbuffers(1, &this->RBO);
    this->name = "Main Frame Buffer";
}

void FrameBuffer::use() {
    std::cout<<"Binding Frame buffer "<<std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER,this->ID);
}

void FrameBuffer::mountTexture(Texture *pTexture) {
    glBindFramebuffer(GL_FRAMEBUFFER, this->ID);
    glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, pTexture->getDimentions().x, pTexture->getDimentions().y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH32F_STENCIL8, GL_RENDERBUFFER,this->RBO);
    std::cout<<"Mounting Texture with coordinates\n";
    std::cout << pTexture->getDimentions().x << "\n";
    std::cout << pTexture->getDimentions().y << "\n";
    this->texture = pTexture;
    glBindTexture(this->texture->type, this->texture->ID);

    std::cout<<"Texture mounted with shader name:"<<this->texture->shaderName<<std::endl;
}

void FrameBuffer::cancel() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void FrameBuffer::useTexture(Texture *texture, GLenum attachement, GLenum textureTarget, unsigned int mipMaplevel) const {
    glBindFramebuffer(GL_FRAMEBUFFER, this->ID);
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachement, textureTarget,texture->ID, mipMaplevel);
}

void FrameBuffer::updateRenderBufferStorage(glm::vec2 dimetions, GLenum format) {
    std::cout<<"Changing RBO storage to X: "<<dimetions.x<< "Y: "<<dimetions.y <<std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, this->ID);
    glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);

    glRenderbufferStorage(GL_RENDERBUFFER, format, dimetions.x, dimetions.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH32F_STENCIL8, GL_RENDERBUFFER, this->RBO);
}

void FrameBuffer::drawToTexture(Shader shader, unsigned int VAO, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
    glBindFramebuffer(GL_FRAMEBUFFER,this->ID);
    shader.use();
    glBindVertexArray(VAO);
    this->useTexture(this->texture, GL_COLOR_ATTACHMENT0, this->texture->type);
    glDrawArrays(GL_TRIANGLE_STRIP, 0.0, 4);
    glBindVertexArray(0);
    this->cancel();
}

