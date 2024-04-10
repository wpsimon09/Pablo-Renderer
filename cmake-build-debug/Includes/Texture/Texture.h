//
// Created by wpsimon09 on 23/12/23.
//

#ifndef CLIONTEST_TEXTURE_H
#define CLIONTEST_TEXTURE_H
#include "glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Shader.h"

class Texture
{
    public:
        unsigned int ID;
        GLenum type;
        Shader *shader;
        const char* path;
        const char* shaderName;

        Texture(GLenum type, const char*shaderName, glm::vec2 dimensions, GLenum colorChannels, GLenum internalFomrat = GL_RGBA32F);
        void updateDimentions(glm::vec2 dimentions);
        void changeFilteringMethod(GLenum mag, GLenum min);
        void changeWrappingMethod(GLenum s, GLenum t, GLenum r = GL_REPEAT);
        void generateMipmap();
        glm::vec2 getDimentions();
        void setShader(Shader shader)
        {
            this->shader= &shader;
        }

        void setFromExisting(unsigned int texutureID)
        {
            this->ID=texutureID;
        }

private:
        glm::vec2 dimensions;
        GLenum colorChannels;
};

#endif //CLIONTEST_TEXTURE_H
