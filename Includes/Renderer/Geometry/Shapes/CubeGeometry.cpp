//
// Created by wpsimon09 on 30/12/23.
//

#include "CubeGeometry.h"

#include <utility>

void CubeGeometry::generateVAO() {
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeof(cube)/sizeof(float), cube, GL_STATIC_DRAW);
}

void CubeGeometry::fillTheVerticies() {

}

CubeGeometry::CubeGeometry(std::string name):Geometry() {

    this->name = std::move(name);
    this->fillTheVerticies();
    this->generateVAO();
}

