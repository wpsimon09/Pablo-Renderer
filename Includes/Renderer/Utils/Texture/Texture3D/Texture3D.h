//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_TEXTURE3D_H
#define PABLO_RENDERER_TEXTURE3D_H

#include "Renderer/Utils/Texture/TextureBase.h"
#include "Debug/DebugLogger.h"

class Texture3D:public TextureBase {
public:
    Texture3D()=default;
    Texture3D(int SCR_WIDTH, int SCR_HEIGHT, GLenum foramt = GL_RGB, unsigned int levels = 1);
;
};

#endif //PABLO_RENDERER_TEXTURE3D_H
