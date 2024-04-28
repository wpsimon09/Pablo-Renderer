//
// Created by wpsimon09 on 28/04/24.
//

#include "AreaLight.h"
#include "ltc_matrix.h"

AreaLight::AreaLight(glm::vec3 position, glm::vec3 color) : Light(position, color) {
    this->LTC = std::make_unique<Texture2D>(64,64,LTC1, GL_FLOAT);
    this->LTCInverse = std::make_unique<Texture2D>(64,64, LTC2, GL_FLOAT);

    auto geometry = std::make_unique<PlaneGeometry>();
    auto material = std::make_unique<BasicMaterialColor>(color);
    this->lightRenderable = std::make_unique<Renderable>(std::move(geometry),std::move(material));
    lightRenderable->transformations->setPosition(this->position->property);
    lightRenderable->transformations->setScale(0.2f, 0.2f, 0.2f);

    this->createLightMatrices();
}

void AreaLight::update(std::shared_ptr<Shader> shader, bool isCastingShadows) {
    Light::update(shader, isCastingShadows);
}

void AreaLight::render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    Light::render(viewMatrix, projectionMatrix);
}

void AreaLight::updateLightViewMatrix() {
    Light::updateLightViewMatrix();
}
