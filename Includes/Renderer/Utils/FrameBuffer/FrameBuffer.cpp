//
// Created by wpsimon09 on 05/02/24.
//

#include "FrameBuffer.h"

FrameBuffer::FrameBuffer() {
    glGenFramebuffers(1, &this->ID);
    glBindFramebuffer(GL_FRAMEBUFFER, this->ID);
}
