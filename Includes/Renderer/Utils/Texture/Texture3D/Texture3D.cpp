//
// Created by wpsimon09 on 15/02/24.
//

#include "Texture3D.h"

Texture3D::Texture3D(int SCR_WIDTH, int SCR_HEIGHT, GLenum colorChannels, GLenum internalFomrat, GLenum dataType) {
    glGenTextures(1, &this->ID);
    glBindTexture(GL_TEXTURE_3D, this->ID);

    for (int i = 0; i < 6; ++i)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, colorChannels, SCR_WIDTH, SCR_HEIGHT, 0,internalFomrat, dataType, nullptr);
    }
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture3D::bind() {
    glBindTexture(GL_TEXTURE_3D, this->ID);
    glGetError();
}

void Texture3D::unbind() {
    glBindTexture(GL_TEXTURE_3D, 0);
    glGetError();
}

void Texture3D::changeFilteringMethod(GLenum mag, GLenum min) {
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, mag);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, min);
}

