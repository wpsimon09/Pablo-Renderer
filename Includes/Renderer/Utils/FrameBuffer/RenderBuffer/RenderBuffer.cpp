//
// Created by wpsimon09 on 05/02/24.
//

#include "RenderBuffer.h"

RenderBuffer::RenderBuffer(int SCR_WIDTH, int SCR_HEIGHT) {
    glGenRenderbuffers(1, &this->ID);
    glBindRenderbuffer(GL_RENDERBUFFER, this->ID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
    glBindRenderbuffer(GL_RENDERBUFFER,0);
}

void RenderBuffer::bind() {
    glBindRenderbuffer(GL_RENDERBUFFER, this->ID);
}

void RenderBuffer::unbind() {
    glBindRenderbuffer(GL_RENDERBUFFER,0);
}

