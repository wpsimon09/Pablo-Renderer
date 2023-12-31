//
// Created by wpsimon09 on 31/12/23.
//

#include "ModelGeometry.h"

#include <utility>

ModelGeometry::ModelGeometry(std::string name, std::vector<Vertex> verticies,std::vector<unsigned int> indecies): Geometry() {
    this->name = std::move(name);
    this->vao = new VAO(std::move(verticies), std::move(indecies));
}
