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

void Light::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        this->position->property.z += lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        this->position->property.z -= lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        this->position->property.x += lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        this->position->property.x -= lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        this->position->property.y -= lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        this->position->property.y += lightSpeed;
}
