//
// Created by wpsimon09 on 14/02/24.
//

#include "BasicMaterialColor.h"

void BasicMaterialColor::configureShader() {
    this->shader->use();
    this->shader->setVec3(this->color->shaderName, this->color->value);

}

BasicMaterialColor::BasicMaterialColor(Shader *shader, glm::vec3 color, std::string shaderName):Material() {
    this->color = new ColorUnifrom(shaderName, color);
    this->shader = shader;
}

