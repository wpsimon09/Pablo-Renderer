//
// Created by wpsimon09 on 28/04/24.
//

#include "DirectionalLight.h"
#include "Renderer/Material/BasicMaterialTexturd/BasicMaterialTextured.h"
#include "Renderer/Geometry/Shapes/ScreenSpaceQuad/ScreenSpaceQuadGeometry.h"

DirectionalLight::DirectionalLight(glm::vec3 color, glm::vec3 position) : Light(color, position) {
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
    this->lightRenderable->getObjectMaterial()->shader->use();
    this->lightRenderable->getObjectMaterial()->shader->setVec3("lightColor", this->color->property);

    shader->use();
    shader->setVec3(this->position->uniformName, this->position->property);
    shader->setVec3(this->color->uniformName, this->calculateFinalLightColor());

    this->updateLightViewMatrix();

    glm::mat4 lightSpaceMatrix = this->lightProjectionMatrix->property * lightViewMatrix->property;
    shader->setMat4("lightMatrix", lightSpaceMatrix);

    this->lightRenderable->transformations->setPosition(this->position->property);
    this->lightRenderable->update();
}

void DirectionalLight::render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    auto shader = lightRenderable->getShader();
    ShaderHelper::setTransfomrationMatrices(shader, lightRenderable->transformations->getModelMatrix(), viewMatrix, projectionMatrix );
    this->lightRenderable->render();
}

void DirectionalLight::renderUi() {
    ImGui::ColorPicker3("Light color", &this->color->property.x,ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs);
    ImGui::SliderFloat("Light intensity", &this->lightStrength,0.0f,50.0f);

    if(ImGui::TreeNodeEx("Position")){
        ImGui::SliderFloat("X", &position->property.x,-50.0f,50.0f);
        ImGui::SliderFloat("Y", &position->property.y,-50.0f,50.0f);
        ImGui::SliderFloat("Z", &position->property.z,-50.0f,50.0f);

        ImGui::TreePop();
    }

}

void DirectionalLight::updateLightViewMatrix() {
    Light::updateLightViewMatrix();
}

