//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_TEXTUREBASE_H
#define PABLO_RENDERER_TEXTUREBASE_H

#include "Renderer/Utils/OGLObject/OGLObject.h"
#include "iostream"
#include "stb_image.h"


class TextureBase : public OGLObject {
public:
    TextureBase()=default;

    GLuint ID;
    GLenum type;
    std::string type_string;
    bool wasFound;
    bool isPBRMaterial;
    std::string fullPath;
    unsigned int samplerID;

    void changeFilteringMethod(GLenum mag, GLenum min);

    virtual void loadFromFile(const char *path){};

    unsigned int getSamplerID() const { return this->samplerID; }

    void setSamplerID(unsigned int ID) { this->samplerID = ID; }

    void bind() override;

    void unbind() override;

    const std::string &getFullPath() const { return this->fullPath; };
protected:
    void loadPNG(const char*path);
    void loadHRI(const char*path);

    int texWidth, texHeight;
private:
    void release() {
        if (ID != 0) {
            // Reset ID to indicate that the texture has been released
        }
    };

public:

    //------------------------
    // C++ RULE 3/5 PRINCIPLES
    //------------------------
    ~TextureBase() { release(); }

    TextureBase(const TextureBase &) = delete;

    TextureBase &operator=(const TextureBase &) = delete;

    TextureBase(TextureBase &&other) noexcept;

    TextureBase &operator=(TextureBase &&other) noexcept;
};


#endif //PABLO_RENDERER_TEXTUREBASE_H
