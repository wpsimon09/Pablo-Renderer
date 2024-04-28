//
// Created by wpsimon09 on 31/12/23.
//

#include "PBRColor.h"

PBRColor::PBRColor(glm::vec3 albedo, float metallic, float rougness, float ao, std::string shaderNamingConvention): Material() {
    this->shader = std::make_shared<Shader>("VertexShader/PBR/PBRVertex-Simple.glsl", "FragmentShader/PBR/PBRFragment.glsl", "PBR shader color");

    this->albedo = std::make_unique<PBRMaterial<glm::vec3>>(albedo, shaderNamingConvention + "Albedo");
    this->rougness = std::make_unique<PBRMaterial<float>>(rougness, shaderNamingConvention + "Rougness");
    this->metalness = std::make_unique<PBRMaterial<float>>(metallic, shaderNamingConvention + "Metalness");
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

void PBRColor::configureShader() {
    this->shader->use();

    this->shader->setVec3(this->albedo->shaderName, *this->albedo->type);
    this->shader->setFloat(this->metalness->shaderName, *this->metalness->type);
    this->shader->setFloat(this->rougness->shaderName, *this->rougness->type);
    this->shader->setFloat(this->ao->shaderName, *this->ao->type);
}

void PBRColor::renderUI(){
    ImGui::ColorPicker3("Color", &this->albedo->type->x);

    if(ImGui::TreeNodeEx("Material properties")){
           ImGui::SliderFloat("Roughens", this->rougness->type.get(), 0.0f, 1.0f);
           ImGui::SliderFloat("Mealness", this->metalness->type.get(), 0.0f, 1.0f);
           ImGui::SliderFloat("AO", this->ao->type.get(), 0.0f, 1.0f);

           ImGui::TreePop();
    }
}

