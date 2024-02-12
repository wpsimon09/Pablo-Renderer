//
// Created by wpsimon09 on 03/01/24.
//

#include "BasicMaterialTextured.h"

#include <utility>

BasicMaterialTextured::BasicMaterialTextured(Shader *shader, const char *path, std::string shaderName) {
    this->shader = shader;
    Texture2D texture(path);
    this->texture = new TextureUniform(std::move(shaderName),std::move(texture));
    this->texture->texture2D.setSamplerID(0);
}

void BasicMaterialTextured::configureShader() {
    this->shader->use();
    this->shader->setInt(this->texture->shaderName, this->texture->texture2D.getSamplerID());

    glActiveTexture(GL_TEXTURE0 + this->texture->texture2D.getSamplerID());
    glBindTexture(GL_TEXTURE_2D, this->texture->texture2D.ID);
}

BasicMaterialTextured::BasicMaterialTextured(Shader* shader,Texture2D texture2D, std::string shaderName) {
    this->shader = shader;
    this->texture = new TextureUniform(shaderName, std::move(texture2D));
}



