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
    this->transformations = new Transformations();
}

Renderable::Renderable(Shader *shader) {
    //default values
    this->objectMaterial = new PBRColor(shader);
    this->objectGeometry = new CubeGeometry();
}

Renderable::Renderable(Geometry *geometry, Material *material, Transformations *transform) {

}


void Renderable::render() {
    this->objectGeometry->render();
}
