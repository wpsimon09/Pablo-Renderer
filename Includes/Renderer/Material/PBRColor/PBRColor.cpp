//
// Created by wpsimon09 on 31/12/23.
//

#include "PBRColor.h"

PBRColor::PBRColor(glm::vec3 albedo,bool supportsIBL,bool supportsAreaLight, std::string name, float metallic, float rougness, float ao, std::string shaderNamingConvention): Material() {
    if(supportsAreaLight){
        this->shader = ShaderManager::getShader(SHADER_AREA_LIGHT_COLOUR);
    }else
        this->shader = ShaderManager::getShader(SHADER_PBR_COLOUR);

    if(name.empty()) {
        this->name = "Colour material" + std::to_string(this->ID);
    }else
        this->name = name;

    this->supportsIBL = supportsIBL;
    this->supportsAreaLight = supportsAreaLight;

    this->albedo = std::make_unique<PBRMaterial<glm::vec3>>(albedo, shaderNamingConvention + "Albedo");
    this->rougness = std::make_unique<PBRMaterial<float>>(rougness, shaderNamingConvention + "Rougness");
    this->metalness = std::make_unique<PBRMaterial<float>>(metallic, shaderNamingConvention + "Metallic");
    this->ao = std::make_unique<PBRMaterial<float>>(ao, shaderNamingConvention + "Ao");
}


std::ostream &operator<<(std::ostream &os, const PBRColor &mat) {
    os<<"PBR material using COLORS has following properties"<<std::endl;

    os<<"===================================================="<<std::endl;
    os<<"SHADER: "<<mat.shader->name<<std::endl;
    os<<"===================================================="<<std::endl;
    return os;
}

void PBRColor::printLog() const {
    std::cout<<*this;
}

glm::vec3 PBRColor::getAlbedoColour() {
    return *this->albedo->type;
}

void PBRColor::configureShader() {
    this->shader->use();
    this->shader->setFloat("supportsIBL", this->supportsIBL);
    this->shader->setVec3(this->albedo->shaderName, *this->albedo->type);
    this->shader->setFloat(this->metalness->shaderName, *this->metalness->type);
    this->shader->setFloat(this->rougness->shaderName, *this->rougness->type);
    this->shader->setFloat(this->ao->shaderName, *this->ao->type);
}

void PBRColor::renderUI(){
    ImGui::PushItemWidth(170);
    ImGui::ColorPicker3("Color", &this->albedo->type->x, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs);

    ImGui::Dummy(ImVec2(20,20));

    ImGui::SliderFloat("Roughens", this->rougness->type.get(), 0.0f, 1.0f);

    ImGui::Dummy(ImVec2(20,20));

    ImGui::SliderFloat("Mealness", this->metalness->type.get(), 0.0f, 1.0f);

    ImGui::Dummy(ImVec2(20,20));

    ImGui::SliderFloat("AO", this->ao->type.get(), 0.0f, 1.0f);

    ImGui::Checkbox("Supports IBL", &this->supportsIBL);
}

