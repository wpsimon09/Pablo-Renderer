//
// Created by wpsimon09 on 06/01/24.
//

#include "Light.h"
#include "Renderer/Material/Material.h"

Light::Light(glm::vec3 position, glm::vec3 color) {
    this->position = std::make_unique<LightProperty<glm::vec3>>(position, "lightPositions[0]");
    this->color = std::make_unique<LightProperty<glm::vec3>>(color, "lightColors[0]");
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

void Light::updateInternal() {
    this->lightRenderable->getObjectMaterial()->shader->use();
    this->lightRenderable->getObjectMaterial()->shader->setVec3("lightColor", this->color->property);
    this->updateLightViewMatrix();
    this->lightRenderable->transformations->setPosition(this->position->property);
    this->lightRenderable->update();

}

void Light::renderUi() {
        ImGui::PushItemWidth(200);
        ImGui::ColorPicker3("Light color", &this->color->property.x,ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs);
        ImGui::SliderFloat("Light intensity", &this->lightStrength,0.0f,50.0f);
        if(ImGui::TreeNodeEx("Position")){
            ImGui::SliderFloat("X", &position->property.x,-50.0f,50.0f);
            ImGui::SliderFloat("Y", &position->property.y,-50.0f,50.0f);
            ImGui::SliderFloat("Z", &position->property.z,-50.0f,50.0f);

            ImGui::TreePop();
        }

}


