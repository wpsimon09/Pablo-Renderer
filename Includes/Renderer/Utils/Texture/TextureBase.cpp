//
// Created by wpsimon09 on 15/02/24.
//

#include "TextureBase.h"

TextureBase::TextureBase(TextureBase &&other) noexcept {

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

}
