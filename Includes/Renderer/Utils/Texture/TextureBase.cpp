//
// Created by wpsimon09 on 15/02/24.
//

#include "TextureBase.h"

TextureBase::TextureBase(TextureBase &&other) noexcept:  ID(other.ID), isPBRMaterial(other.isPBRMaterial), fullPath(other.fullPath), samplerID(other.samplerID), wasFound(other.wasFound) {

}

TextureBase &TextureBase::operator=(TextureBase &&other) noexcept {
    if (this != &other) {

        glDeleteTextures(1, &this->ID);
        std::swap(ID, other.ID);
        std::swap(isPBRMaterial, other.isPBRMaterial);
        std::swap(fullPath, other.fullPath);
        std::swap(wasFound ,other.wasFound);
        std::swap(samplerID, other.samplerID);

        // Reset other
        other.ID = 0;
    }
    return *this;;

}

void TextureBase::changeFilteringMethod(GLenum mag, GLenum min) {
    glBindTexture(this->type, this->ID);
    glTexParameteri(this->type,GL_TEXTURE_MAG_FILTER, mag);
    glTexParameteri(this->type,GL_TEXTURE_MIN_FILTER, min);
}

void TextureBase::bind() {
    glBindTexture(this->type, this->ID);
    glGetError();
}

void TextureBase::unbind() {
    glBindTexture(this->type,0);
    glGetError();
}
