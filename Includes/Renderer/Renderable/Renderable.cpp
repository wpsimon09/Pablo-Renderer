//
// Created by wpsimon09 on 30/12/23.
//

#include "Renderable.h"

std::ostream &operator<<(std::ostream &os, Renderable &obj) {

    os<<" =========================="<<std::endl;
    os<<" Renderable object created "<<std::endl;
    os<<" ========================== "<<std::endl;

    os<<" ========================== "<<std::endl;
    os<<" MATERIAL INFO: "<<std::endl ;
    os<<"==========================="<<std::endl;
    obj.objectMaterial->printLog();


    return os;
}


Renderable::Renderable(Geometry *geometry, Material *material, std::string name) {
    this->name = name;
    this->objectGeometry = geometry;
    this->objectMaterial = material;
    this->modelMatrix = glm::mat4(1.0f);
}

Renderable::Renderable(Shader *shader) {
    //default values
    this->objectMaterial = new PBRColor(shader);
    this->objectGeometry = new CubeGeometry();
    this->modelMatrix = glm::mat4(1.0f);
}

void Renderable::render() {
    this->objectMaterial->shader->use();
    this->objectMaterial->shader->setMat4("projection", this->projectionMatrix);
    this->objectMaterial->shader->setMat4("view", this->viewMatrix);
    this->objectMaterial->configureShader();
    this->objectGeometry->render();
}

void Renderable::setProjectionMatrix(const glm::mat4 &projectionMatrix) {
    Renderable::projectionMatrix = projectionMatrix;
}

void Renderable::setViewMatrix(const glm::mat4 &viewMatrix) {
    Renderable::viewMatrix = viewMatrix;
}

