//
// Created by wpsimon09 on 31/12/23.
//

#ifndef PABLO_RENDERER_TEXTURE2D_H
#define PABLO_RENDERER_TEXTURE2D_H

#include "glad.h"
#include "stb_image.h"
#include "iostream"
#include "memory"
#include "Renderer/Utils/OGLObject/OGLObject.h"
#include "Renderer/Utils/Texture/TextureBase.h"
#include "Debug/DebugLogger.h"

class Texture2D : public TextureBase  {
public:
    Texture2D();

    explicit Texture2D(const char *path, bool isPBRMaterial = false);

    explicit Texture2D(int width, int height, GLenum foramt = GL_RGB);
    ~Texture2D() = default;
};


#endif //PABLO_RENDERER_TEXTURE2D_H
