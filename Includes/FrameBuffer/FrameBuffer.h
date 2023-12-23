//
// Created by wpsimon09 on 23/12/23.
//

#ifndef CLIONTEST_FRAMEBUFFER_H
#define CLIONTEST_FRAMEBUFFER_H

#include "glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Texture.h"

class FrameBuffer {
    public:
        unsigned int ID;
        FrameBuffer();
    private:
        unsigned int RBO;
        unsigned int texture;
};

FrameBuffer::FrameBuffer() {
    glGenFramebuffers(1, &this->ID);
    glGenRenderbuffers(1, &this->RBO);

    glBindFramebuffer(GL_FRAMEBUFFER, this->ID);
    glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);


    glRenderbufferStorage()
}


#endif //CLIONTEST_FRAMEBUFFER_H
