//
// Created by wpsimon09 on 28/04/24.
//

#include "DirectionalLight.h"
#include "Renderer/Material/BasicMaterialTexturd/BasicMaterialTextured.h"
#include "Renderer/Geometry/Shapes/ScreenSpaceQuad/ScreenSpaceQuadGeometry.h"

DirectionalLight::DirectionalLight(glm::vec3 color, glm::vec3 position) : Light(color, position) {
    this->type = "Directional";
    auto geometry = std::make_unique<ScreenSpaceQuadGeometry>();
    auto material = std::make_unique<BasicMaterialTextured>(std::make_shared<Shader>("VertexShader/AdvancedLightning/LightSourceVertex.glsl", "FragmentShader/AdvancedLightning/LightSourceFragment.glsl", "light sourece"), "Assets/Textures/AdvancedLightning/sun.png", "lightTexture");
    material->shader->use();
    material->shader->setVec3("lightColor", this->color->property);
    this->lightRenderable = std::make_shared<Renderable>(std::move(geometry), std::move(material));
    lightRenderable->transformations->setPosition(this->position->property);
    lightRenderable->transformations->setScale(0.2f,0.2f, 0.2f);

    //light matrix calculations
    this->createLightMatrices();
}

void DirectionalLight::update(std::shared_ptr<Shader> shader, bool isCastingShadows) {
    /***
     * @note this updates the shader which this light is contributing to
     */
    this->updateInternal();

    shader->use();
    shader->setVec3(this->position->uniformName, this->position->property);
    shader->setVec3(this->color->uniformName, this->calculateFinalLightColor());

    if(isCastingShadows){
        glm::mat4 lightSpaceMatrix = this->lightProjectionMatrix->property * lightViewMatrix->property;
        shader->setMat4("lightMatrix", lightSpaceMatrix);
    }
}

void DirectionalLight::render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    auto shader = lightRenderable->getShader();
    ShaderHelper::setTransfomrationMatrices(shader, lightRenderable->transformations->getModelMatrix(), viewMatrix, projectionMatrix );
    this->lightRenderable->render();
}

void DirectionalLight::renderUi() {
    //render light specific for each light
    Light::renderUi();
}

void DirectionalLight::updateLightViewMatrix() {
    Light::updateLightViewMatrix();
}

