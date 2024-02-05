//
// Created by wpsimon09 on 31/12/23.
//

#include "Texture2D.h"

Texture2D::Texture2D(const char *path, bool isPBRMaterial) {
    this->isPBRMaterial = isPBRMaterial;
    this->fullPath = path;
    glGenTextures(1, &this->ID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
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

        this->wasFound = true;

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

const std::string &Texture2D::getFullPath() const {
    return fullPath;
}

void Texture2D::changeFilteringMethod(GLenum mag, GLenum min) {
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
}

Texture2D::Texture2D(int SCR_WIDTH, int SCR_HEIGHT, GLenum colorChannels, GLenum internalFomrat, GLenum dataType) {
    this->isPBRMaterial = false;
    this->wasFound = true;

    glGenTextures(1, &this->ID);

    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, colorChannels, SCR_WIDTH, SCR_HEIGHT, 0, internalFomrat, dataType, NULL);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,0);
}

void Texture2D::bind() {
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glGetError();
}

void Texture2D::unbind() {
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glGetError();
}
