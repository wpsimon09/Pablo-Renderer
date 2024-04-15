//
// Created by wpsimon09 on 15/04/24.
//

#include "Renderer/Utils/Camera/Camera.h"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"

Camera::Camera(glm::vec3 center, glm::vec3 up) {
    this->center = center;
    this->worldUp = up;
    this->projection = glm::perspective(glm::radians(65.0f), (float)GLFWHelper::getScreenWidth() / (float)GLFWHelper::getScreenHeight(), 0.1f, 200.0f);
}


glm::mat4 Camera::getPojectionMatix() {
    return this->projection;
}

glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(this->position,center, this->worldUp);
}

glm::vec3 Camera::getPosition() {
    return this->position;
}

void Camera::update(std::shared_ptr<Shader> shader) {
    shader->use();
    shader->setVec3("camPos", this->position);
}



