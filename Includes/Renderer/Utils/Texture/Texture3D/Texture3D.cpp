//
// Created by wpsimon09 on 15/02/24.
//

#include "Texture3D.h"

Texture3D::Texture3D(int SCR_WIDTH, int SCR_HEIGHT, GLenum foramt, unsigned int levels): TextureBase() {
    this->type = GL_TEXTURE_CUBE_MAP;
    this->type_string = "GL_TEXTURE_CUBE_MAP";
    this->wasFound = true;
    this->isPBRMaterial = false;
    this->fullPath = "generated by OpenGL";
    this->texWidth = SCR_WIDTH;
    this->texHeight = SCR_HEIGHT;

    glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &this->ID);
    glCheckError();

    glBindTexture(GL_TEXTURE_CUBE_MAP, this->ID);
    glCheckError();

    glTexStorage2D(GL_TEXTURE_CUBE_MAP , levels, foramt, SCR_WIDTH, SCR_HEIGHT);
    glCheckError();

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glCheckError();

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glCheckError();

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glCheckError();

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, levels >1 ? GL_LINEAR_MIPMAP_LINEAR:GL_LINEAR);
    glCheckError();

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glCheckError();

    if(levels > 1){
        glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
        glCheckError();
    }
}


