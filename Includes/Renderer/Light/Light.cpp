//
// Created by wpsimon09 on 06/01/24.
//

#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color) {
    this->position = new LightProperty(position, "lightPosition[0]");
    this->color = new LightProperty(color, "lightColors[0]");
}

void Light::update(Shader *shader) {
    shader->use();
    shader->setVec3(this->position->uniformName, this->position->property);
    shader->setVec3(this->color->uniformName, this->color->property);
}
