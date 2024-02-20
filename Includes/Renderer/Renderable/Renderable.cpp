//
// Created by wpsimon09 on 30/12/23.
//

#include "Renderable.h"

#include <utility>

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


Renderable::Renderable(std::unique_ptr<Geometry> geometry, std::unique_ptr<Material>  material, std::string name) {
    this->name = std::move(name);
    this->objectGeometry = std::move(geometry);
    this->objectMaterial = std::move(material);
    this->modelMatrix = glm::mat4(1.0f);
}

Renderable::Renderable(std::shared_ptr<Shader> shader) {
    //default values
    this->objectMaterial = std::make_unique<PBRColor>(std::move(shader));
    this->objectGeometry = std::make_unique<CubeGeometry>();
    this->modelMatrix = glm::mat4(1.0f);
}

void Renderable::render() {
    this->objectMaterial->configureShader();
    this->objectGeometry->render();
}

std::shared_ptr<Shader> Renderable::getShader() {
    return this->objectMaterial->shader;
}

Renderable::Renderable() {

}


