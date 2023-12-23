//
// Created by wpsimon09 on 23/12/23.
//

#ifndef CLIONTEST_FRAMEBUFFER_H
#define CLIONTEST_FRAMEBUFFER_H

#include "glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Texture/Texture.h"
#include "Shader.h"

#define SHAPE_CUBE 1;
#define SHAPE_PLANE 2;

class FrameBuffer {
    public:
        unsigned int ID;
        Texture *texture;

        FrameBuffer();
        void use();
        void mountTexture(Texture *texture);
    private:
        unsigned int RBO;
};


#endif //CLIONTEST_FRAMEBUFFER_H
