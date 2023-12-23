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

        Texture(GLenum type, unsigned int texture,const char*shaderName, glm::vec2 dimensions, GLenum colorChannels);
        glm::vec2 getDimentions();
private:
        glm::vec2 dimensions;
        GLenum colorChannels;
};

#endif //CLIONTEST_TEXTURE_H
