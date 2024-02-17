//
// Created by wpsimon09 on 15/02/24.
//

#include "Texture3D.h"

Texture3D::Texture3D(int SCR_WIDTH, int SCR_HEIGHT, GLenum colorChannels, GLenum internalFomrat, GLenum dataType):TextureBase() {
    this->type = GL_TEXTURE_CUBE_MAP;
    this->type_string = "GL_TEXTURE_CUBE_MAP";
    this->wasFound = true;
    this->isPBRMaterial = false;
    this->fullPath = "generated by OpenGL";
    this->texWidth = SCR_WIDTH;
    this->texHeight = SCR_HEIGHT;

    glCreateTextures(1,GL_TEXTURE_CUBE_MAP, &this->ID);

    for (int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, colorChannels, SCR_WIDTH, SCR_HEIGHT, 0,internalFomrat, dataType, nullptr);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

}


