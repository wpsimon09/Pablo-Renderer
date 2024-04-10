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

/***
 * Class representing GL_TEXTURE_2D
 * @inherit TextureBase
 */
class Texture2D : public TextureBase  {
public:
    Texture2D();

    /***
     * Loads texture from the file
     * @param path path to the 2D texture
     * @param isPBRMaterial is the loaded texture part of the PBR material workflow ?
     * @note texture should end with .png
     */
    explicit Texture2D(const char *path, bool isPBRMaterial = false);

    /***
     * Creates texture with no color data but just with allocated memory
     * @param width widht of the texture
     * @param height height of the texture
     * @param foramt format for texture to use @def GL_RGB
     */
    explicit Texture2D(int width, int height, GLenum foramt = GL_RGB);
    ~Texture2D() = default;
};


#endif //PABLO_RENDERER_TEXTURE2D_H
