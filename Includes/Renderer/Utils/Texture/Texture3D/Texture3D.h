//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_TEXTURE3D_H
#define PABLO_RENDERER_TEXTURE3D_H

#include "Renderer/Utils/Texture/TextureBase.h"

class Texture3D:public TextureBase {
public:
    Texture3D(int SCR_WIDTH, int SCR_HEIGHT, GLenum colorChannels = GL_RGB, GLenum internalFomrat = GL_RGB,
              GLenum dataType = GL_UNSIGNED_BYTE);
;
};

#endif //PABLO_RENDERER_TEXTURE3D_H
