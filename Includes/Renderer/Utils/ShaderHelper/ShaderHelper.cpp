//
// Created by wpsimon09 on 12/01/24.
//

#include "ShaderHelper.h"

void ShaderHelper::setTransfomrationMatrices(Shader *shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
    shader->use();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    shader->setMat4("model", model);
}

void ShaderHelper::setTextureToShader(Shader *shader,  std::unique_ptr<TextureBase> texture, std::string shaderName) {
    shader->use();
    shader->setInt(shaderName, texture->samplerID);
    glActiveTexture(GL_TEXTURE0 + texture->samplerID);
    glCheckError();
    glBindTexture(GL_TEXTURE_2D, texture->ID);
    glCheckError();
}

