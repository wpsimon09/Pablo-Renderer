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

void Geometry::render() const {
    this->bindVertexArrays();
    glGetError();
    glDrawArrays(this->shapes, 0,this->numVerticies);
    glGetError();
}

std::vector<glm::vec3> Geometry::getAreaLightCornerPoints() {
    return std::vector<glm::vec3>();
}

