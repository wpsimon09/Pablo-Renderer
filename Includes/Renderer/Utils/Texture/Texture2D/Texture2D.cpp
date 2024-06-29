//
// Created by wpsimon09 on 31/12/23.
//

#include "Texture2D.h"

Texture2D::Texture2D(const char *path, bool isPBRMaterial,bool loadToGl, MATERIAL_TEXTURE_TYPE textureType ):TextureBase() {
    this->isPBRMaterial = isPBRMaterial;
    this->texturePath = path;
    this->type = GL_TEXTURE_2D;
    this->textureType = textureType;
    this->type_string = "GL_TEXTURE_2D";
    this->internalFormat = GL_RGBA;
    if(loadToGl){
        this->isInGL = true;
        glCreateTextures(GL_TEXTURE_2D, 1, &this->ID);
        glCheckError();
    }

    this->loadPNG(path,loadToGl);
}

Texture2D::Texture2D() {

}

Texture2D::Texture2D(int width, int height, float *data, GLenum format) {
    this->type = GL_TEXTURE_2D;
    this->isPBRMaterial = false;
    this->wasFound = true;
    this->type_string = "GL_TEXTURE_2D";
    this->texturePath = "Generated by OpenGL";
    this->texWidth = width;
    this->texHeight = height;
    this->internalFormat = format;
    this->isInGL = true;

    glCreateTextures(GL_TEXTURE_2D, 1, &this->ID);
    glCheckError();

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glCheckError();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,width, height, 0, GL_RGBA, format, data);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glCheckError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glCheckError();

    glBindTexture(GL_TEXTURE_2D, 0);
    glCheckError();
}


Texture2D::Texture2D(int width, int height, GLenum foramt): TextureBase() {
    this->type = GL_TEXTURE_2D;
    this->isPBRMaterial = false;
    this->wasFound = true;
    this->type_string = "GL_TEXTURE_2D";
    this->texturePath = "Generated by OpenGL";
    this->texWidth = width;
    this->texHeight = height;
    this->internalFormat = foramt;
    this->isInGL = true;

    // ------------------
    // PBR_TEXTURE_MAPS GENERATION
    // -------------------
    glCreateTextures(GL_TEXTURE_2D,1, &this->ID);
    glCheckError();

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glCheckError();

    glTexStorage2D(GL_TEXTURE_2D, 1, foramt, width, height);
    glCheckError();


    // ------------------
    // PBR_TEXTURE_MAPS PARAMETERS
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

void Texture2D::passToOpenGL() {
    if(!isInGL){
        glCreateTextures(GL_TEXTURE_2D, 1, &this->ID);
        glCheckError();

        glBindTexture(GL_TEXTURE_2D, this->ID);
        glCheckError();

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->texWidth, this->texHeight, 0, format, GL_UNSIGNED_BYTE, this->textureData);
        glCheckError();

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        this->isInGL = true;
    }
    if(textureData != nullptr){
        stbi_image_free(textureData);
    }
    textureData = nullptr;
}




