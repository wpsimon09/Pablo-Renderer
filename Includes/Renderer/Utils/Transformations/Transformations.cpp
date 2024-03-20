//
// Created by wpsimon09 on 30/12/23.
//

#include "Transformations.h"

Transformations::Transformations(glm::vec3 position, glm::vec3 scale, glm::vec3 rotations) {
    this->position = position;
    this->rotations = rotations;
    this->scale = scale;
}

Transformations::Transformations() {
    this->position = glm::vec3(0.0f, 0.0f, 0.0F);
    this->rotations = glm::vec3(0.0f, 0.0f, 0.0f);
    this->scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

const glm::vec3 &Transformations::getPosition() const {
    return position;
}

void Transformations::setPosition(const glm::vec3 &position) {
    this->isDirty = true;
    Transformations::position = position;
}

const glm::vec3 &Transformations::getRotations() const {
    return rotations;
}

void Transformations::setRotations(const glm::vec3 &rotations) {
    this->isDirty = true;
    Transformations::rotations = rotations;
}

const glm::vec3 &Transformations::getScale() const {
    return scale;
}

void Transformations::setScale(const glm::vec3 &scale) {
    this->isDirty = true;
    Transformations::scale = scale;
}

void Transformations::computeModelMatrix() {
    this->m_modelMatrix = this->computeLocalModelMatrix();
    this->isDirty = false;
}

void Transformations::computeModelMatrix(const glm::mat4 &parentGlobalMatrix) {
    this->m_modelMatrix =  parentGlobalMatrix * this->computeLocalModelMatrix();
    this->isDirty = false;
}

glm::mat4 Transformations::computeLocalModelMatrix() {
    //set rotations on X axis
    const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
                                             glm::radians(this->rotations.x),
                                             glm::vec3(1.0f, 0.0f, 0.0f));
    //set rotations on Y axis
    const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
                                             glm::radians(this->rotations.y),
                                             glm::vec3(0.0f, 1.0f, 0.0f));
    //set rotations on Z axis
    const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
                                             glm::radians(this->rotations.z),
                                             glm::vec3(0.0f, 0.0f, 1.0f));

    // Y * X * Z
    const glm::mat4 roationMatrix = transformY * transformX * transformZ;

    // translation * rotation * scale (also know as TRS matrix)
    return glm::translate(glm::mat4(1.0f), this->position) *
           roationMatrix *
           glm::scale(glm::mat4(1.0f), this->scale);
}

void Transformations::setPosition(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
}

void Transformations::setRotations(float x, float y, float z) {
    this->rotations = glm::vec3(x, y, z);
}

void Transformations::setScale(float x, float y, float z) {
    this->scale = glm::vec3(x, y, z);
}


