//
// Created by wpsimon09 on 06/01/24.
//

#include "Light.h"
#include "Renderer/Geometry/Shapes/ScreenSpaceQuad/ScreenSpaceQuadGeometry.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Material/BasicMaterialTexturd/BasicMaterialTextured.h"

Light::Light(glm::vec3 position, glm::vec3 color) {
    this->position = std::make_unique<LightProperty<glm::vec3>>(position, "lightPositions[0]");
    this->color = std::make_unique<LightProperty<glm::vec3>>(color, "lightColors[0]");

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

void Light::update(std::shared_ptr<Shader> shader, bool isCastingShadows) {
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

}



void Light::render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    auto shader = lightRenderable->getShader();
    ShaderHelper::setTransfomrationMatrices(shader, lightRenderable->transformations->getModelMatrix(), viewMatrix, projectionMatrix );
    this->lightRenderable->render();
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
    ImGui::ColorPicker3("Light color", &this->color->property.x,ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs);
    ImGui::SliderFloat("Light intensity", &this->lightStrength,0.0f,50.0f);

    if(ImGui::TreeNodeEx("Position")){
            ImGui::SliderFloat("X", &position->property.x,-50.0f,50.0f);
            ImGui::SliderFloat("Y", &position->property.y,-50.0f,50.0f);
            ImGui::SliderFloat("Z", &position->property.z,-50.0f,50.0f);

            ImGui::TreePop();
    }

}


