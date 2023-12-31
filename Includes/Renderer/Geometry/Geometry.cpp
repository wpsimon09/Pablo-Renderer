//
// Created by wpsimon09 on 30/12/23.
//

#include "Geometry.h"

GLuint Geometry::getVertexArrays() {
    return this->vao->ID;
}

std::string Geometry::getName() {
    return this->name;
}

void Geometry::bindVertexArrays() {
    this->vao->bind();
}

void Geometry::unbindVertexArrays() {
    this->vao->unbind();
}

