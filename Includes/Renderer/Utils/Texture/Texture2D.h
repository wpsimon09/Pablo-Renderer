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


class Texture2D : public OGLObject {
public:
    GLuint ID;
    Texture2D();

    explicit Texture2D(const char *path, bool isPBRMaterial = false);

    explicit Texture2D(int SCR_WIDTH, int SCR_HEIGHT, GLenum colorChannels = GL_RGB, GLenum internalFomrat = GL_RGB,
                       GLenum dataType = GL_UNSIGNED_BYTE);

    bool wasFound;
    bool isPBRMaterial;

    void bind() override;

    void unbind() override;

private:
    unsigned int samplerID;
    std::string fullPath;

    void release();

public:
    unsigned int getSamplerID() const { return this->samplerID; }

    void setSamplerID(unsigned int ID) { this->samplerID = ID; }

    const std::string &getFullPath() const;

    void changeFilteringMethod(GLenum mag, GLenum min);

public:
    //------------------------
    // C++ RULE 3/5 PRINCIPLES
    //------------------------
    ~Texture2D() { release(); }

    Texture2D(const Texture2D &) = delete;

    Texture2D &operator=(const Texture2D &) = delete;

    Texture2D(Texture2D &&other) noexcept ;

    Texture2D&operator = (Texture2D &&other) noexcept ;
};


#endif //PABLO_RENDERER_TEXTURE2D_H
