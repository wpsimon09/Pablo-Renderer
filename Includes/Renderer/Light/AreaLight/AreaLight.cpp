//
// Created by wpsimon09 on 28/04/24.
//

#include "AreaLight.h"
#include "ltc_matrix.h"

AreaLight::AreaLight(glm::vec3 position, glm::vec3 color) : Light(position, color) {
    this->LTC = std::make_unique<Texture2D>(64,64,LTC1, GL_FLOAT);
    this->LTCInverse = std::make_unique<Texture2D>(64,64, LTC2, GL_FLOAT);

    this->scale = std::make_unique<LightProperty<glm::vec3>>(glm::vec3(1.0f, 2.0f, 1.0f), "scale");
    auto geometry = std::make_unique<PlaneGeometry>();
    auto material = std::make_unique<BasicMaterialColor>(color);
    this->lightRenderable = std::make_unique<Renderable>(std::move(geometry),std::move(material));
    lightRenderable->transformations->setPosition(this->position->property);
    lightRenderable->transformations->setScale(0.2f, 0.2f, 0.2f);

    this->createLightMatrices();
}

void AreaLight::update(std::shared_ptr<Shader> shader, bool isCastingShadows) {
    this->lightRenderable->transformations->setPosition(this->position->property);
    this->lightRenderable->transformations->setScale(this->scale->property);
    this->lightRenderable->update();
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

}
