//
// Created by wpsimon09 on 15/02/24.
//

#include <utility>
#include "TextureBase.h"

TextureBase::TextureBase(TextureBase &&other) noexcept: ID(other.ID), isPBRMaterial(other.isPBRMaterial),
                                                        fullPath(other.fullPath), samplerID(other.samplerID),
                                                        wasFound(other.wasFound), type(other.type),
                                                        type_string(other.type_string), texWidth(other.texWidth),
                                                        texHeight(other.texHeight){

}

TextureBase &TextureBase::operator=(TextureBase &&other) noexcept {
    if (this != &other) {
        release();
        ID = std::exchange(other.ID, 0);
        isPBRMaterial = other.isPBRMaterial;
        fullPath = std::move(other.fullPath);
        samplerID = other.samplerID;
        wasFound = other.wasFound;
        type = other.type;
        type_string = std::move(other.type_string);
        texWidth = other.texWidth;
        texHeight = other.texHeight;
    }
    return *this;;

}

void TextureBase::changeFilteringMethod(GLenum mag, GLenum min) {
    glBindTexture(this->type, this->ID);
    glTexParameteri(this->type, GL_TEXTURE_MAG_FILTER, mag);
    glTexParameteri(this->type, GL_TEXTURE_MIN_FILTER, min);
}

void TextureBase::bind() {
    glBindTexture(this->type, this->ID);
    glGetError();
}

void TextureBase::unbind() {
    glBindTexture(this->type, 0);
    glGetError();
}

void TextureBase::loadPNG(const char *path, bool flip) {
    stbi_set_flip_vertically_on_load(flip);
    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
        this->texWidth = width;
        this->texHeight = height;
        this->wasFound = true;

        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, this->ID);
        glCheckError();
        //OpenGL throwing error at forestRock/displacement map
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glCheckError();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        stbi_image_free(data);
    } else {
        this->wasFound = false;
        std::cerr << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

}

void TextureBase::loadHRI(const char *path) {
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrComponents;
    float *data = stbi_loadf(path, &width, &height, &nrComponents, 0);
    if (data) {
        this->texWidth = width;
        this->texHeight = height;
        this->wasFound = true;


        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(this->type, this->ID);
        glTexImage2D(this->type, 0, GL_RGBA32F, width, height, 0, format, GL_FLOAT, data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        std::cout << "HDRI TEXTURE LOADED \xE2\x9C\x93" << std::endl;
        std::string base_filename = path;
        base_filename = base_filename.substr(base_filename.find_last_of("/\\") + 1);
        std::cout << "Image:" << base_filename << std::endl << std::endl;

        stbi_image_free(data);
    } else {
        this->wasFound = false;
        std::cerr << "HDRI Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }
    stbi_set_flip_vertically_on_load(false);
}

void TextureBase::generateMipMaps() {
    //glBindTexture(this->type, this->ID);
    //glGenerateMipmap(this->type);
}

void TextureBase::setUnpackAlignment(int alignment) {
    this->bind();
    glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
    this->unbind();
}
