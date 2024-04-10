//
// Created by wpsimon09 on 31/12/23.
//

#include "ModelGeometry.h"

#include <utility>


ModelGeometry::ModelGeometry(std::string name, std::vector<Vertex> verticies,std::vector<unsigned int> indecies): Geometry() {
    this->name = std::move(name);
    this->shapes = GL_TRIANGLES;
    this->vao = std::make_unique<VAO>(std::move(verticies), std::move(indecies));
    this->numIndecies = this->vao->getNumberOfIndecies();
    this->numVerticies = this->vao->getNumberOfVerticies();
}

void ModelGeometry::render() const {
    this->vao->bind();
    glDrawElements(this->shapes, this->numIndecies, GL_UNSIGNED_INT, 0);

    this->vao->unbind();
    glGetError();
}


