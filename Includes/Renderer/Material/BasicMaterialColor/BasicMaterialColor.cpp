//
// Created by wpsimon09 on 14/02/24.
//

#include "BasicMaterialColor.h"

void BasicMaterialColor::configureShader() {
    this->shader->use();
    this->shader->setVec3(this->color->shaderName, this->color->value);

}

BasicMaterialColor::BasicMaterialColor(std::shared_ptr<Shader> shader, glm::vec3 color, std::string shaderName):Material(std::move(shader)) {
    this->color = std::make_unique<ColorUnifrom>(shaderName, color);
    this->supportsIBL = false;
}

