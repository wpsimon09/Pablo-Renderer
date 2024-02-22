//
// Created by wpsimon09 on 31/12/23.
//

#include "PBRColor.h"

PBRColor::PBRColor(std::shared_ptr<Shader> shader, glm::vec3 albedo, float metallic, float rougness, float ao, std::string shaderNamingConvention): Material(std::move(shader)) {
    this->albedo = std::make_unique<PBRMaterial<glm::vec3>>(albedo, "Albedo");
    this->rougness = std::make_unique<PBRMaterial<float>>(rougness, shaderNamingConvention + "Rougness");
    this->metalness = std::make_unique<PBRMaterial<float>>(metallic, shaderNamingConvention + "Metalness");
    this->ao = std::make_unique<PBRMaterial<float>>(ao, shaderNamingConvention + "Ao");
}


PBRMaterial<glm::vec3> *PBRColor::getAlbedo() const {
    return albedo.get();
}

PBRMaterial<float> *PBRColor::getMetalness() const {
    return metalness.get();
}

PBRMaterial<float> *PBRColor::getRougness() const {
    return rougness.get();
}

PBRMaterial<float> *PBRColor::getAo() const {
    return ao.get();
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

