//
// Created by wpsimon09 on 30/12/23.
//

#include "PlaneGeometry.h"
#include "planeVertexData.h"

PlaneGeometry::PlaneGeometry(std::string name): Geometry() {
    this->name = std::move(name);
    this->vao = std::make_unique<VAO>(planeVertexData, sizeof(planeVertexData)/sizeof(float));
    this->shapes = GL_TRIANGLES;
    this->numVerticies = 6;
}
