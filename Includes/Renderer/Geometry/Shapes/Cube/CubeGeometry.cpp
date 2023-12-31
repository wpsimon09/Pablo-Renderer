//
// Created by wpsimon09 on 30/12/23.
//

#include "CubeGeometry.h"
#include "cubeVertexData.h"
#include <utility>

CubeGeometry::CubeGeometry(std::string name):Geometry() {

    this->name = std::move(name);
    this->vao = new VAO(cubeData, sizeof(cubeData) / sizeof(float));
    this->verticies = 36;
    this->indecies = 0;
    this->shapes = GL_TRIANGLES;

}

