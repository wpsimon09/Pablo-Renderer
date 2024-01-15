//
// Created by wpsimon09 on 06/01/24.
//

#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color) {
    this->position = new LightProperty(position, "lightPositions[0]");
    this->color = new LightProperty(color, "lightColors[0]");
}

void Light::update(Shader *shader) {
    shader->use();
    shader->setVec3(this->position->uniformName, this->position->property);
    shader->setVec3(this->color->uniformName, this->color->property);
}

void Light::setX(float pos) {
    this->position->property.x = pos;
}

void Light::setY(float pos) {
    this->position->property.y = pos;
}

void Light::setZ(float pos) {
    this->position->property.z= pos;
}
