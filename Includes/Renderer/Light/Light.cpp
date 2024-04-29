//
// Created by wpsimon09 on 06/01/24.
//

#include "Light.h"
#include "Renderer/Material/Material.h"

Light::Light(glm::vec3 position, glm::vec3 color) {
    this->position = std::make_unique<LightProperty<glm::vec3>>(position, "lightPositions[0]");
    this->color = std::make_unique<LightProperty<glm::vec3>>(color, "lightColors[0]");
}

void Light::update(std::shared_ptr<Shader> shader, bool isCastingShadows) {

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




void Light::render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {

}

void Light::createLightMatrices() {
    glm::mat4 lightView = glm::lookAt(this->position->property, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    this->lightViewMatrix = std::make_unique<LightProperty<glm::mat4>>(lightView, "lightViewMatrix");

    glm::mat4 lightPojection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, this->lightNearPlane, this->lightFarPlane);
    this->lightProjectionMatrix = std::make_unique<LightProperty<glm::mat4>>(lightPojection, "lightProjectionMatrix");

}

void Light::updateLightViewMatrix() {
    glm::mat4 lightView = glm::lookAt(this->position->property, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    this->lightViewMatrix = std::make_unique<LightProperty<glm::mat4>>(lightView, "lightViewMatrix");
}

void Light::renderUi() {

}

void Light::updateInternal() {
    this->lightRenderable->getObjectMaterial()->shader->use();
    this->lightRenderable->getObjectMaterial()->shader->setVec3("lightColor", this->color->property);
    this->updateLightViewMatrix();
    this->lightRenderable->transformations->setPosition(this->position->property);
    this->lightRenderable->update();

}


