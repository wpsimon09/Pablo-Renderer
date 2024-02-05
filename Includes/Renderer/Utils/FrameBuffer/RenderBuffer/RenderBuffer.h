//
// Created by wpsimon09 on 05/02/24.
//

#ifndef PABLO_RENDERER_RENDERBUFFER_H
#define PABLO_RENDERER_RENDERBUFFER_H
#include "glad/glad.h"

class RenderBuffer {
public:
    RenderBuffer(int SCR_WIDTH, int SCR_HEIGHT);
    void bind();
    GLuint ID;
};


#endif //PABLO_RENDERER_RENDERBUFFER_H
