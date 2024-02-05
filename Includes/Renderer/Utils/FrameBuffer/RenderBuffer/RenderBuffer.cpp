//
// Created by wpsimon09 on 05/02/24.
//

#include "RenderBuffer.h"

RenderBuffer::RenderBuffer() {
    glGenRenderbuffers(1, &this->ID);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
}
