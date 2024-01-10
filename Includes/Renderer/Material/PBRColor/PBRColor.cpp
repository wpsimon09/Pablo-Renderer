//
// Created by wpsimon09 on 31/12/23.
//

#include "PBRColor.h"

PBRColor::PBRColor(Shader* shader, glm::vec3 albedo, float metallic, float rougness, float ao, std::string shaderNamingConvention): Material(shader) {
    this->albedo = new PBRMaterial(albedo, shaderNamingConvention+"Albedo");
    this->rougness = new PBRMaterial(rougness, shaderNamingConvention+"Rougness");
    this->metalness = new PBRMaterial(metallic, shaderNamingConvention+"Metalness");
    this->ao = new PBRMaterial(ao, shaderNamingConvention+"Ao");
}

PBRColor::PBRColor(Shader* shader, std::string shaderNamingConvention): Material(shader) {
    this->albedo = new PBRMaterial(glm::vec3(0.2f,0.45f,0.2f), shaderNamingConvention+"Albedo");
    this->rougness = new PBRMaterial(0.2f, shaderNamingConvention+"Rougness");
    this->metalness = new PBRMaterial(0.8f, shaderNamingConvention+"Metalness");
    this->ao = new PBRMaterial(0.5f, shaderNamingConvention+"Ao");
}

PBRMaterial<glm::vec3> *PBRColor::getAlbedo() const {
    return albedo;
}

PBRMaterial<float> *PBRColor::getMetalness() const {
    return metalness;
}

PBRMaterial<float> *PBRColor::getRougness() const {
    return rougness;
}

PBRMaterial<float> *PBRColor::getAo() const {
    return ao;
}

std::ostream &operator<<(std::ostream &os, const PBRColor &mat) {
    os<<"PBR material using COLORS has following properties"<<std::endl;

    os<<"===================================================="<<std::endl;
    os<<"SHADER: "<<mat.shader->name<<std::endl;
    os<<"===================================================="<<std::endl;

    os<< "ALBEDO VALUES:" << std::endl;
    os<<"RED: "<<mat.albedo->type.r<<std::endl;
    os<<"GREEN: "<<mat.albedo->type.g<<std::endl;
    os<<"BLUE: "<<mat.albedo->type.b<<std::endl;
    os<<"SHADER NAME: "<<mat.albedo->shaderName<<std::endl;

    os<<"==================================================="<<std::endl;

    os<< "METALNESS VALUES:" << std::endl;
    os<<"STRENGTH: "<<mat.metalness->type<<std::endl;
    os<<"SHADER NAME: "<<mat.metalness->shaderName<<std::endl;

    os<<"==================================================="<<std::endl;

    os<< "ROUGNESS VALUES:" << std::endl;
    os<<"STRENGTH: "<<mat.rougness->type<<std::endl;
    os<<"SHADER NAME: "<<mat.rougness->shaderName<<std::endl;

    os<<"==================================================="<<std::endl;

    os<< "AO VALUES:" << std::endl;
    os<<"STRENGTH: "<<mat.ao->type<<std::endl;
    os<<"SHADER NAME: "<<mat.ao->shaderName<<std::endl<<std::endl;

    os<<"==================================================="<<std::endl;
    return os;
}

void PBRColor::printLog() const {
    std::cout<<*this;
}

void PBRColor::configureShader() {
    this->shader->use();
    this->shader->setVec3(this->albedo->shaderName, this->albedo->type);
    this->shader->setFloat(this->metalness->shaderName, this->metalness->type);
    //this->shader->setVec3(this->albedo->shaderName, this->albed o->type);
    //this->shader->setVec3(this->albedo->shaderName, this->albedo->type);
}

