//
// Created by wpsimon09 on 23/12/23.
//

#include "FrameBuffer.h"


FrameBuffer::FrameBuffer() {
    glGenFramebuffers(1, &this->ID);
    glGenRenderbuffers(1, &this->RBO);

    glBindFramebuffer(GL_FRAMEBUFFER, this->ID);
    glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, this->texture->getDimentions().x, this->texture->getDimentions().y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH32F_STENCIL8, GL_RENDERBUFFER,this->RBO);
}

void FrameBuffer::use() {
    glBindFramebuffer(GL_FRAMEBUFFER,this->ID);
}

void FrameBuffer::mountTexture(Texture *texture) {
    this->texture = texture;
}
