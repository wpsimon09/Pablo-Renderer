//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_TEXTUREHDRI_H
#define PABLO_RENDERER_TEXTUREHDRI_H

#include "Renderer/Utils/Texture/TextureBase.h"

class TextureHDRi:public TextureBase {
public:
    explicit TextureHDRi(const char*path);
};


#endif //PABLO_RENDERER_TEXTUREHDRI_H
