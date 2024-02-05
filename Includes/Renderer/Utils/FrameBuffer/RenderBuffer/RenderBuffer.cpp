//
// Created by wpsimon09 on 05/02/24.
//

#include "RenderBuffer.h"

RenderBuffer::RenderBuffer(int SCR_WIDTH, int SCR_HEIGHT) {
    glGenRenderbuffers(1, &this->ID);
    glGetError();
    glBindRenderbuffer(GL_RENDERBUFFER, this->ID);
    glGetError();
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
    glGetError();
    glBindRenderbuffer(GL_RENDERBUFFER,0);
    glGetError();
}

void RenderBuffer::bind() {
    glBindRenderbuffer(GL_RENDERBUFFER, this->ID);
    glGetError();
}
