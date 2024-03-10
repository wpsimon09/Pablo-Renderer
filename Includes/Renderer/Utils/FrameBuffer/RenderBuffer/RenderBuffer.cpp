//
// Created by wpsimon09 on 05/02/24.
//

#include "RenderBuffer.h"

RenderBuffer::RenderBuffer(int SCR_WIDTH, int SCR_HEIGHT) {
    glGenRenderbuffers(1, &this->ID);
    glCheckError();

    glBindRenderbuffer(GL_RENDERBUFFER, this->ID);
    glCheckError();

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
    glCheckError();

    glBindRenderbuffer(GL_RENDERBUFFER,0);
    glCheckError();
}

void RenderBuffer::bind() {
    glBindRenderbuffer(GL_RENDERBUFFER, this->ID);
    glCheckError();
}

void RenderBuffer::unbind() {
    glBindRenderbuffer(GL_RENDERBUFFER,0);
    glCheckError();
}

void RenderBuffer::updateDimetions(unsigned int width, unsigned int height) {
    this->bind();

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glCheckError();

    this->unbind();
}

