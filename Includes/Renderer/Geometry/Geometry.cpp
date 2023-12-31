//
// Created by wpsimon09 on 30/12/23.
//

#include "Geometry.h"

GLuint Geometry::getVertexArrays() const {
    return this->vao->ID;
}

std::string Geometry::getName() const {
    return this->name;
}

void Geometry::bindVertexArrays()const {
    this->vao->bind();
}

void Geometry::unbindVertexArrays()const  {
    this->vao->unbind();
}

