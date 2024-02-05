//
// Created by wpsimon09 on 05/02/24.
//

#ifndef PABLO_RENDERER_RENDERBUFFER_H
#define PABLO_RENDERER_RENDERBUFFER_H
#include "glad/glad.h"
#include "Renderer/Utils/OGLObject/OGLObject.h"

class RenderBuffer: public OGLObject{
public:
    RenderBuffer(int SCR_WIDTH, int SCR_HEIGHT);

    void bind() override;

    void unbind() override;
};


#endif //PABLO_RENDERER_RENDERBUFFER_H
