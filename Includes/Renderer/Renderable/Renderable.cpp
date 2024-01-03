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

Renderable::Renderable(Geometry *geometry, Material *material, Transformations *transform) {
    this->objectGeometry = geometry;
    this->objectMaterial = material;
    this->transformations = transform;
}

Renderable::Renderable(Shader *shader) {
    this->objectMaterial = new PBRColor(shader);
    this->objectGeometry = new CubeGeometry();
    this->transformations = new Transformations();
}
