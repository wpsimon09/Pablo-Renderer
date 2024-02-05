//
// Created by wpsimon09 on 31/12/23.
//

#ifndef PABLO_RENDERER_TEXTURE2D_H
#define PABLO_RENDERER_TEXTURE2D_H

#include "glad.h"
#include "stb_image.h"
#include "iostream"
#include "Renderer/Utils/OGLObject/OGLObject.h"


class Texture2D: public OGLObject {
public:
    void bind() override;

    void unbind() override;

    bool isPBRMaterial;
    bool wasFound;
    Texture2D();
    explicit Texture2D(const char* path, bool isPBRMaterial = false);
    explicit Texture2D(int SCR_WIDTH, int SCR_HEIGHT,  GLenum colorChannels = GL_RGB, GLenum internalFomrat = GL_RGB, GLenum dataType =GL_UNSIGNED_BYTE);
private:
    unsigned int samplerID;
    std::string fullPath;
public:
    unsigned int getSamplerID() {return this->samplerID;}
    void setSamplerID(unsigned int ID){ this->samplerID = ID; }
    const std::string &getFullPath() const;
    void changeFilteringMethod(GLenum mag, GLenum min);
};


#endif //PABLO_RENDERER_TEXTURE2D_H
