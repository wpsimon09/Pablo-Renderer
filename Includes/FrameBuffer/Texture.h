//
// Created by wpsimon09 on 23/12/23.
//

#ifndef CLIONTEST_TEXTURE_H
#define CLIONTEST_TEXTURE_H
#include "glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

class Texture
{
    public:
        unsigned int ID;
        GLenum type;
        const char* path;
        const char* shaderName;

        Texture(GLenum type, const char * path,const char*shaderName, glm::vec2 dimensions, GLenum colorChannels);
        glm::vec2 getDimentions();
private:
        glm::vec2 dimensions;
        GLenum colorChannels;

};

Texture::Texture(GLenum type, const char *path,const char*shaderName, glm::vec2 dimensions, GLenum colorChannels) {
    glGenTextures(1, &this->ID);
    glBindTexture(type, this->ID);
    this->dimensions = dimensions;
    this->shaderName = shaderName;
    if (type == GL_TEXTURE_CUBE_MAP)
    {
        for (int i = 0; i < 6; ++i)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, GL_RGB16F, dimensions.x, dimensions.y, 0, colorChannels, GL_FLOAT, nullptr);
        }
        glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else if (type == GL_TEXTURE_2D)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, dimensions.x, dimensions.y, 0, colorChannels, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    this->type=type;
}

glm::vec2 Texture::getDimentions() {
    return this->dimensions;
}


#endif //CLIONTEST_TEXTURE_H
