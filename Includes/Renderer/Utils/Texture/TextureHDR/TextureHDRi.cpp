//
// Created by wpsimon09 on 15/02/24.
//

#include "TextureHDRi.h"

TextureHDRi::TextureHDRi(const char *path):TextureBase() {
    this->type = GL_TEXTURE_2D;
    this->fullPath = path;
    this->isPBRMaterial = false;
    glCreateTextures(GL_TEXTURE_2D,1, &this->ID );
    this->loadHRI(path);
}

