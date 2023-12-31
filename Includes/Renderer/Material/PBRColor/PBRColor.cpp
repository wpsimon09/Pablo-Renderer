//
// Created by wpsimon09 on 31/12/23.
//

#include "PBRColor.h"

PBRColor::PBRColor(glm::vec3 albedo, float metallic, float rougness, float ao): Material() {
    this->albedo = new PBRMaterial(albedo, "albedo");
    this->rougness = new PBRMaterial(rougness, "rougness");
    this->metalness = new PBRMaterial(metallic, "metalness");
    this->ao = new PBRMaterial(ao, "ao");
}

PBRColor::PBRColor(): Material() {
    this->albedo = new PBRMaterial(glm::vec3(0.2f,0.45f,0.2f), "albedo");
    this->rougness = new PBRMaterial(0.2f, "rougness");
    this->metalness = new PBRMaterial(0.8f, "metalness");
    this->ao = new PBRMaterial(0.5f, "ao");
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

