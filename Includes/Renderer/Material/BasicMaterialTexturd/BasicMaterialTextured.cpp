//
// Created by wpsimon09 on 03/01/24.
//

#include "BasicMaterialTextured.h"

BasicMaterialTextured::BasicMaterialTextured(Shader *shader, const char *path) {
    this->shader = shader;
    this->texture = new TextureUniform("FragmentColor", new Texture2D(path));
    this->texture->texture2D->setSamplerID(0);
}

void BasicMaterialTextured::configureShader() {
    this->shader->use();
    this->shader->setInt(this->texture->shaderName, this->texture->texture2D->getSamplerID());

    glActiveTexture(GL_TEXTURE0 + this->texture->texture2D->getSamplerID());
    glBindTexture(GL_TEXTURE_2D, this->texture->texture2D->ID);
}

BasicMaterialTextured::BasicMaterialTextured(Texture2D *texture2D) {
    this->shader = shader;
    this->texture = new TextureUniform("FragmentColor", texture2D);
}



