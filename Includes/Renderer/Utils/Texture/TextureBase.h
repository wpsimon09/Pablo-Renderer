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
    TextureBase() {};

    GLuint ID;
    GLenum type;
    std::string type_string;
    bool wasFound;
    bool isPBRMaterial;
    std::string fullPath;
    unsigned int samplerID;
    int texWidth, texHeight;

    void changeFilteringMethod(GLenum mag, GLenum min);

    virtual void loadFromFile(const char *path){};

    unsigned int getSamplerID() const { return this->samplerID; }

    void setSamplerID(unsigned int ID) { this->samplerID = ID; }

    void bind() override;

    void unbind() override;

    void generateMipMaps();

    void setUnpaceAlligment(int alligment);

    const std::string &getFullPath() const { return this->fullPath; };
protected:
    void loadPNG(const char*path);
    void loadHRI(const char*path);

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
    ~TextureBase() = default; //{ release(); }

    TextureBase(const TextureBase &) = default;

    TextureBase &operator=(const TextureBase &) = delete;

    TextureBase(TextureBase &&other) noexcept;

    TextureBase &operator=(TextureBase &&other) noexcept;
};


#endif //PABLO_RENDERER_TEXTUREBASE_H
