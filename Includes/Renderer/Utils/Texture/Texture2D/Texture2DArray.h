//
// Created by wpsimon09 on 19/05/24.
//

#ifndef PABLO_RENDERER_TEXTURE2DARRAY_H
#define PABLO_RENDERER_TEXTURE2DARRAY_H

#include "Renderer/Utils/Texture/TextureBase.h"
#include "Renderer/Utils/Texture/Texture2D/Texture2D.h"
#include "memory"
#include "vector"

class Texture2DArray:public TextureBase {
public:
    Texture2DArray(std::vector<std::shared_ptr<Texture2D>> textures);

    bool isValidArray(std::vector<std::shared_ptr<Texture2D>> texutres);

    void add(std::shared_ptr<Texture2D> texture);

    void bind() override;

    void unbind() override;
private:
    int textureCount = 0;
    std::vector<std::shared_ptr<Texture2D>> textures;
};


#endif //PABLO_RENDERER_TEXTURE2DARRAY_H
