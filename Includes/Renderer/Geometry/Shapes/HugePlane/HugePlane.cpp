//
// Created by wpsimon09 on 08/02/24.
//

#include "HugePlane.h"
#include "hugePlaneVertexData.h"

HugePlane::HugePlane(std::string name) {
    this->name = std::move(name);
    this->vao = std::make_unique<VAO>(hugePlaneVerticies, sizeof(hugePlaneVerticies)/sizeof(float));
    this->shapes = GL_TRIANGLES;
    this->numVerticies = 6;
}
