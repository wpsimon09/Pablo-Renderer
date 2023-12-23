//
// Created by wpsimon09 on 23/12/23.
//

#ifndef CLIONTEST_FRAMEBUFFER_H
#define CLIONTEST_FRAMEBUFFER_H

#include "glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Texture.h"
#include "Shader.h"
#include "DrawingFunctions.h"

#define SHAPE_CUBE 1;
#define SHAPE_PLANE 2;

class FrameBuffer {
    public:
        unsigned int ID;
        FrameBuffer(Texture *frameBufferTexture);
        Texture *texture;
        void render(Shader shader, glm::mat4 projection , glm::mat4 view,unsigned int VAO,  glm::mat4 model = glm::mat4(1.0f) );
    private:
        unsigned int RBO;

};

FrameBuffer::FrameBuffer(Texture *frameBufferTexture) {
    this->texture = frameBufferTexture;

    glGenFramebuffers(1, &this->ID);
    glGenRenderbuffers(1, &this->RBO);

    glBindFramebuffer(GL_FRAMEBUFFER, this->ID);
    glBindRenderbuffer(GL_RENDERBUFFER, this->RBO);

    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, this->texture->getDimentions().x, this->texture->getDimentions().y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH32F_STENCIL8, GL_RENDERBUFFER,this->RBO);
}

void FrameBuffer::render(Shader shader, glm::mat4 projection, glm::mat4 view, unsigned int VAO, glm::mat4 model) {
    shader.use();
    shader.setInt(this->texture->shaderName, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(this->texture->type, this->texture->ID);

    glViewport(0, 0,this->texture->getDimentions().x, this->texture->getDimentions().y);

    if (this->texture->type == GL_TEXTURE_CUBE_MAP)
    {
        for (int i = 0; i < 6; ++i)
        {
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, envCubeMap, 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            DrawCube(shader,model, view, projection, VAO);
        }
    }

}


#endif //CLIONTEST_FRAMEBUFFER_H
