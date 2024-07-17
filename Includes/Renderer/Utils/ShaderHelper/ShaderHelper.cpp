//
// Created by wpsimon09 on 12/01/24.
//

#include "ShaderHelper.h"

void ShaderHelper::setTransfomrationMatrices(std::shared_ptr<Shader> shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection) {
    shader->use();
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
    shader->setMat4("model", model);
}

void ShaderHelper::setTextureToShader(std::shared_ptr<Shader> shader, TextureBase texture, std::string shaderName) {
    shader->use();
    shader->setInt(shaderName, texture.samplerID);
    glActiveTexture(GL_TEXTURE0 + texture.samplerID);
    glCheckError();
    glBindTexture(texture.type, texture.ID);
    glCheckError();
}

void
ShaderHelper::setTextureToShader(std::shared_ptr<Shader> shader, const TextureBase &texture, std::string shaderName,
                                 int samplerID) {
    glActiveTexture(GL_TEXTURE0 + samplerID);
    glCheckError();

    shader->use();
    shader->setInt(shaderName, samplerID);

    glBindTexture(texture.type, texture.ID);
    glCheckError();
}