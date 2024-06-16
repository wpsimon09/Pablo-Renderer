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


Renderable::Renderable(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material>  material, std::string name) {
    this->name = std::move(name);
    this->objectGeometry = std::move(geometry);
    this->objectMaterial = std::move(material);
    this->modelMatrix = glm::mat4(1.0f);
    this->transformations = std::make_unique<Transformations>();

}

Renderable::Renderable(std::shared_ptr<Shader> shader) {
    //default values
    this->objectMaterial = std::make_unique<PBRColor>();
    this->objectGeometry = std::make_unique<CubeGeometry>();
    this->modelMatrix = glm::mat4(1.0f);
    this->transformations = std::make_unique<Transformations>();
}

void Renderable::render() {
    if(isLineOnly){
        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    }else{
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        this->objectMaterial->shader->use();
        this->objectMaterial->shader->setFloat("isModel", this->isModel);
        this->objectMaterial->shader->setFloat("reciviesShadow", this->recievesShadow);
        this->objectMaterial->configureShader();
    }
    this->objectGeometry->render();
}

std::shared_ptr<Shader> Renderable::getShader() {
    return this->objectMaterial->shader;
}

Renderable::Renderable() {
}

const std::shared_ptr<Material> Renderable::getObjectMaterial() const {
    return objectMaterial;
}

void Renderable::update() {
        transformations->computeModelMatrix();
        this->modelMatrix = transformations->getModelMatrix();
}

void Renderable::renderGeomtry() {
    this->objectGeometry->render();
}


