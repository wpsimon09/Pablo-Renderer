//
// Created by wpsimon09 on 23/12/23.
//

#ifndef CLIONTEST_FRAMEBUFFER_H
#define CLIONTEST_FRAMEBUFFER_H

#include "glad.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "Texture/Texture.h"
#include "Shader.h"

class FrameBuffer {
    public:
        std::string name;
        unsigned int ID;
        Texture *texture;

        FrameBuffer();
        void use();
        void cancel();
        void mountTexture(Texture *pTexture);
        void useTexture(Texture *texture, GLenum attachement, GLenum textureTarget,unsigned int mipMaplevel = 0 ) const;
        void updateRenderBufferStorage(glm::vec2 dimetions, GLenum format = GL_DEPTH_COMPONENT24);
        void drawToTexture(Shader shader, unsigned int VAO, glm::mat4 model = glm::mat4(1.0f), glm::mat4 view = glm::mat4(1.0f), glm::mat4 projection = glm::mat4(1.0f));
    private:
        Shader* shader;
        unsigned int RBO;
};


#endif //CLIONTEST_FRAMEBUFFER_H
