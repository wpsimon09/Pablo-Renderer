//
// Created by wpsimon09 on 26/05/24.
//

#include "SkyBox.h"

SkyBox::SkyBox(std::shared_ptr<TextureBase> skyBox, std::string shaderName):Renderable() {
    this->objectMaterial = std::make_shared<SkyBoxMaterial>(skyBox, shaderName);
    this->objectGeometry = std::make_shared<CubeGeometry>();
    this->skyBoxUniformName = shaderName;
}

void SkyBox::setSkyBoxTexture(std::shared_ptr<TextureBase> newTexture) {
    this->objectMaterial = std::make_shared<SkyBoxMaterial>(newTexture, this->skyBoxUniformName);
}

void SkyBox::renderUI() {
    ImGui::Checkbox("Is SkyboxVisible", &this->isVisible);
}

void SkyBox::render() {
    if(isVisible){
        this->objectMaterial->configureShader();
        this->objectGeometry->render();
    }
}


