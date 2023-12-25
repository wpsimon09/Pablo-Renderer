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
    std::cout<<"Mounting pTexture with coordinates\n";
    std::cout << pTexture->getDimentions().x << "\n";
    std::cout << pTexture->getDimentions().y << "\n";
    this->texture = pTexture;
    glBindTexture(this->texture->type, this->texture->ID);

    std::cout<<"Texture mounted with shader name:"<<this->texture->shaderName<<std::endl;
}

void FrameBuffer::cancel() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::useTexture(Texture *texture, GLenum attachement, GLenum textureTarget, float mipMaplevel) const {
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachement, textureTarget, this->texture->ID, mipMaplevel);
}

