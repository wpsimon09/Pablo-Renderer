//
// Created by wpsimon09 on 15/02/24.
//

#include "TextureHDRi.h"

TextureHDRi::TextureHDRi(const char *path):TextureBase() {
    this->type = GL_TEXTURE_2D;
    this->type_string = "GL_TEXTURE_2D (HDR)";
    this->fullPath = path;
    this->isPBRMaterial = false;
    glCreateTextures(GL_TEXTURE_2D,1, &this->ID );
    this->samplerID = 0;
    this->loadHRI(path);
}

