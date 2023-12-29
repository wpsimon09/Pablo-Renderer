//
// Created by wpsimon09 on 29/12/23.
//

#ifndef CLIONTEST_FRAMEBUFFERDEBUG_H
#define CLIONTEST_FRAMEBUFFERDEBUG_H

#include "Texture/Texture.h"

class FrameBufferDebug :public Texture{
public:
    FrameBufferDebug(GLenum type, const char*shaderName, glm::vec2 dimensions, GLenum colorChannels, GLenum internalFomrat = GL_RGBA32F);
    void draw(Shader shader,unsigned int VAO, Texture* texture);
    void draw(Shader shader,unsigned int VAO, unsigned int texture);

};


#endif //CLIONTEST_FRAMEBUFFERDEBUG_H
