//
// Created by wpsimon09 on 03/01/24.
//

#include "BasicMaterialTextured.h"

#include <utility>

BasicMaterialTextured::BasicMaterialTextured(std::shared_ptr<Shader> shader, const char *path, std::string shaderName):Material(std::move(shader)) {
    Texture2D texture(path);
    this->texture = std::make_unique<TextureUniform>(std::move(shaderName),std::move(texture));
    this->texture->texture2D.setSamplerID(0);
}

void BasicMaterialTextured::configureShader() {
    this->shader->use();
    this->shader->setInt(this->texture->shaderName, this->texture->texture2D.getSamplerID());

    glActiveTexture(GL_TEXTURE0 + this->texture->texture2D.getSamplerID());
    glBindTexture(GL_TEXTURE_2D, this->texture->texture2D.ID);
}

BasicMaterialTextured::BasicMaterialTextured(std::shared_ptr<Shader> shader, TextureBase texture2D, std::string shaderName): Material(std::move(shader)) {
    this->texture = std::make_unique<TextureUniform>(std::move(shaderName), std::move(texture2D));
}





