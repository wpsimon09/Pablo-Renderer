//
// Created by wpsimon09 on 31/12/23.
//

#include "Texture2D.h"

Texture2D::Texture2D(const char *path, bool isPBRMaterial):TextureBase() {
    this->isPBRMaterial = isPBRMaterial;
    this->fullPath = path;
    glCreateTextures(GL_TEXTURE_2D, 1, &this->ID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        this ->wasFound = true;

        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, this->ID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);



        stbi_image_free(data);
    }
    else
    {
        this->wasFound = false;
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }


}

Texture2D::Texture2D() {
}


Texture2D::Texture2D(int SCR_WIDTH, int SCR_HEIGHT, GLenum colorChannels, GLenum internalFomrat, GLenum dataType) {
    this->type = GL_TEXTURE_2D;
    this->isPBRMaterial = false;
    this->wasFound = true;

    glGenTextures(1, &this->ID);

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, colorChannels, SCR_WIDTH, SCR_HEIGHT, 0, internalFomrat, dataType, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //chceck the texture parameters here
    glBindTexture(GL_TEXTURE_2D,0);
}


void Texture2D::loadFromFile(const char *path) {
}


