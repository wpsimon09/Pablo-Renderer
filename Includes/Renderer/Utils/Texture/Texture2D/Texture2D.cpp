//
// Created by wpsimon09 on 31/12/23.
//

#include "Texture2D.h"

Texture2D::Texture2D(const char *path, bool isPBRMaterial):TextureBase() {
    this->isPBRMaterial = isPBRMaterial;
    this->fullPath = path;
    this->type = GL_TEXTURE_2D;
    this->type_string = "GL_TEXTURE_2D";
    glCreateTextures(GL_TEXTURE_2D, 1, &this->ID);
    glCheckError();

    this->loadPNG(path);

}

Texture2D::Texture2D() {
}


Texture2D::Texture2D(int width, int height, GLenum foramt): TextureBase() {
    this->type = GL_TEXTURE_2D;
    this->isPBRMaterial = false;
    this->wasFound = true;
    this->type_string = "GL_TEXTURE_2D";
    this->fullPath = "Generated by OpenGL";
    this->texWidth = width;
    this->texHeight = height;

    // ------------------
    // TEXTURE GENERATION
    // -------------------
    glCreateTextures(GL_TEXTURE_2D,1, &this->ID);
    glCheckError();

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glCheckError();

    glTexStorage2D(GL_TEXTURE_2D, 1, foramt, width, height);
    glCheckError();


    // ------------------
    // TEXTURE PARAMETERS
    // -------------------
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glCheckError();

    // RELEASE
    glBindTexture(GL_TEXTURE_2D,0);
    glCheckError();
}



