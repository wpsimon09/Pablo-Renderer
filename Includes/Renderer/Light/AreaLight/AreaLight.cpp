//
// Created by wpsimon09 on 28/04/24.
//

#include "AreaLight.h"
#include "ltc_matrix.h"

AreaLight::AreaLight(glm::vec3 position, glm::vec3 color) : Light(position, color) {
    this->type = "Area";

    this->ltc = std::make_unique<Texture2D>(64, 64, LTC, GL_FLOAT);
    this->ltc->shaderName = "LTC";
    this->ltc->setSamplerID(0);

    this->color->uniformName = "lightColor";

    this->ltcInverse = std::make_unique<Texture2D>(64, 64, LTC_Inverse, GL_FLOAT);
    this->ltcInverse->shaderName = "LTC_Inverse";
    this->ltcInverse->setSamplerID(1);

    this->scale = std::make_unique<LightProperty<glm::vec3>>(glm::vec3(1.2f, 1.0f, 2.2f), "scale");
    this->rotation = std::make_unique<LightProperty<glm::vec3>>(glm::vec3(0.0f, 0.0f, 0.0f), "rotation");

    auto geometry = std::make_unique<PlaneGeometry>();
    auto material = std::make_unique<BasicMaterialColor>(color);

    material->shader->use();
    material->shader->setVec3("lightColor", this->color->property);

    this->lightRenderable = std::make_unique<Renderable>(std::move(geometry), std::move(material));
    lightRenderable->transformations->setPosition(this->position->property);
    lightRenderable->transformations->setScale(this->scale->property);
    lightRenderable->transformations->setRotations(this->rotation->property);

    this->createLightMatrices();
}

void AreaLight::update(std::shared_ptr<Shader> shader, bool isCastingShadows) {
    this->lightRenderable->transformations->setRotations(this->rotation->property);
    this->lightRenderable->transformations->setScale(this->scale->property);

    this->updateInternal();

    auto m = this->lightRenderable->transformations->getModelMatrix();
    this->sendCornersToShader(this->transformCorners(m), shader);

    shader->use();
    shader->setVec3("lightColor", this->calculateFinalLightColor());
    ShaderHelper::setTextureToShader(shader, *this->ltc, this->ltc->shaderName);
    ShaderHelper::setTextureToShader(shader, *this->ltcInverse, this->ltcInverse->shaderName);

}

void AreaLight::render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
    auto shader = lightRenderable->getShader();
    ShaderHelper::setTransfomrationMatrices(shader, lightRenderable->transformations->getModelMatrix(), viewMatrix,
                                            projectionMatrix);

    this->lightRenderable->render();
}

void AreaLight::updateLightViewMatrix() {
    Light::updateLightViewMatrix();
}

void AreaLight::renderUi() {
    if (ImGui::TreeNodeEx(this->type.c_str())) {

        Light::renderUi();
        if (ImGui::TreeNodeEx("Rotation")) {
            ImGui::SliderFloat("X", &this->rotation->property.x, 0.0f, 360.0f);
            ImGui::SliderFloat("Y", &this->rotation->property.y, 0.0f, 360.0f);
            ImGui::SliderFloat("Z", &this->rotation->property.z, 0.0f, 360.0f);

            ImGui::TreePop();
        }

        if (ImGui::TreeNodeEx("Dimensions")) {

            ImGui::SliderFloat("Width", &this->scale->property.x, 0.0f, 10.0f);
            ImGui::SliderFloat("Height", &this->scale->property.z, 0.0f, 10.0f);

            ImGui::TreePop();
        }

        ImGui::TreePop();
    }
}

std::vector<glm::vec3> AreaLight::transformCorners(glm::mat4 modelMatrix) {
    std::vector<glm::vec3> transformedCorner;

    auto corners = this->lightRenderable->getRenderableGeometry()->getAreaLightCornerPoints();
    //TODO try to send the matrix to the shader and preform transformation there and send points to the vertex shader of the material instad of the fragment shader
    for (auto corner: corners) {
        //transform the edge of the area light
        transformedCorner.emplace_back(glm::vec4(corner, 1.0f) * modelMatrix);
    }

    /***
     * Check if transformation was successful
     */
    if (transformedCorner.size() == corners.size()) {
        return transformedCorner;
    } else
        throw std::logic_error("Not every corner was transformed");
}

void AreaLight::sendCornersToShader(std::vector<glm::vec3> corners, std::shared_ptr<Shader> shader) {
    for (int corner = 0; corner < corners.size(); ++corner) {
        shader->use();
        shader->setVec3("areaLightCorners["+std::to_string(corner)+"]",corners[corner]);
    }
}
