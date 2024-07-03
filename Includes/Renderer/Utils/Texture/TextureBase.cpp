//
// Created by wpsimon09 on 15/02/24.
//

#include <utility>
#include "TextureBase.h"

TextureBase::TextureBase(TextureBase &&other) noexcept: ID(other.ID), isPBRMaterial(other.isPBRMaterial),
                                                        texturePath(other.texturePath), samplerID(other.samplerID),
                                                        wasFound(other.wasFound), type(other.type),
                                                        type_string(other.type_string), texWidth(other.texWidth),
                                                        texHeight(other.texHeight), textureData(other.textureData),
                                                        format(other.format){

}

TextureBase &TextureBase::operator=(TextureBase &&other) noexcept {
    if (this != &other) {
        release();
        ID = std::exchange(other.ID, 0);
        isPBRMaterial = other.isPBRMaterial;
        texturePath = std::move(other.texturePath);
        samplerID = other.samplerID;
        wasFound = other.wasFound;
        type = other.type;
        type_string = std::move(other.type_string);
        texWidth = other.texWidth;
        texHeight = other.texHeight;
        textureData = other.textureData;
        format = other.format;
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

std::string TextureBase::getFileName() {
    std::string base_filename = texturePath;
    base_filename = base_filename.substr(base_filename.find_last_of("/\\") + 1);
    return base_filename;
}

void TextureBase::loadPNG(const char *path,bool loadToGl, bool flip) {
    stbi_set_flip_vertically_on_load(flip);
    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data) {
        this->texWidth = width;
        this->texHeight = height;
        this->wasFound = true;

        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        if(loadToGl){

            glBindTexture(GL_TEXTURE_2D, this->ID);
            glCheckError();

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->texWidth, this->texHeight, 0, format, GL_UNSIGNED_BYTE, data);
            glCheckError();

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }else{
            this->textureData = data;
        }

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

        std::cout << "HDRI PBR_TEXTURE_MAPS LOADED \xE2\x9C\x93" << std::endl;
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
    this->bind();
    glGenerateMipmap(this->type);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glCheckError();
}

void TextureBase::setUnpackAlignment(int alignment) {
    this->bind();
    glPixelStorei(GL_UNPACK_ALIGNMENT, alignment);
    this->unbind();
}

/*

void TextureBase::processToOpenGL(GLenum numberOfChanels) {
    if(this->textureData != nullptr) {
        glBindTexture(GL_TEXTURE_2D, this->ID);
        glCheckError();

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->texWidth, this->texHeight, 0, numberOfChanels, GL_UNSIGNED_BYTE,
                     this->textureData);
        glCheckError();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


        stbi_image_free(this->textureData);
    }else
        throw std::domain_error("Data of the texture are empty or texture was not found");
}
*/

