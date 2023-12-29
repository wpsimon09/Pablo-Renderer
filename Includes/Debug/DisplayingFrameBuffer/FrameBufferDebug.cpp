//
// Created by wpsimon09 on 29/12/23.
//

#include "FrameBufferDebug.h"

FrameBufferDebug::FrameBufferDebug(GLenum type, const char *shaderName, glm::vec2 dimensions, GLenum colorChannels,
                                   GLenum internalFomrat) : Texture(type, shaderName, dimensions, colorChannels,internalFomrat) {

}

void FrameBufferDebug::draw(Shader shader, unsigned int VAO, Texture *texture) {
    shader.use();
    shader.setInt("attachment", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(texture->type, texture->ID);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}
