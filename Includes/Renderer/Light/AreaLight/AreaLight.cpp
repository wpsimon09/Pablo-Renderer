//
// Created by wpsimon09 on 28/04/24.
//

#include "AreaLight.h"
#include "ltc_matrix.h"

AreaLight::AreaLight(glm::vec3 position, glm::vec3 color) : Light(position, color) {
    this->type = "Area";

    this->LTC = std::make_unique<Texture2D>(64,64,LTC1, GL_FLOAT);
    this->LTCInverse = std::make_unique<Texture2D>(64,64, LTC2, GL_FLOAT);

    this->scale = std::make_unique<LightProperty<glm::vec3>>(glm::vec3(1.0f, 2.0f, 1.0f), "scale");
    auto geometry = std::make_unique<PlaneGeometry>();
    auto material = std::make_unique<BasicMaterialColor>(color);
    material->shader->use();
    material->shader->setVec3("lightColor", this->color->property);

    this->lightRenderable = std::make_unique<Renderable>(std::move(geometry),std::move(material));
    lightRenderable->transformations->setPosition(this->position->property);
    lightRenderable->transformations->setScale(4.2f, 1.0f, 4.2f);

    this->createLightMatrices();
}

void AreaLight::update(std::shared_ptr<Shader> shader, bool isCastingShadows) {
    this->lightRenderable->transformations->setScale(this->scale->property);
    this->updateInternal();
}

void AreaLight::render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    auto shader = lightRenderable->getShader();
    ShaderHelper::setTransfomrationMatrices(shader, lightRenderable->transformations->getModelMatrix(), viewMatrix, projectionMatrix );

    this->lightRenderable->render();
}

void AreaLight::updateLightViewMatrix() {
    Light::updateLightViewMatrix();
}

void AreaLight::renderUi() {
    Light::renderUi();
}
