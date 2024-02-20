//
// Created by wpsimon09 on 16/02/24.
//

#include "SkyBoxMaterial.h"

#include <utility>

SkyBoxMaterial::SkyBoxMaterial(std::shared_ptr<Shader> shader, std::unique_ptr<Texture3D> skyBox, std::string shaderName):Material(std::move(shader)) {
    this->cubeMapUnifrom = new CubeMapUnifrom(std::move(skyBox), std::move(shaderName));
    this->cubeMapUnifrom->cubeMap->setSamplerID(0);
}

void SkyBoxMaterial::configureShader() {
    this->shader->use();
    this->shader->setInt(cubeMapUnifrom->shaderName,this->cubeMapUnifrom->cubeMap->samplerID);
    glActiveTexture(GL_TEXTURE0 +  this->cubeMapUnifrom->cubeMap->samplerID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, this->cubeMapUnifrom->cubeMap->ID);
}
