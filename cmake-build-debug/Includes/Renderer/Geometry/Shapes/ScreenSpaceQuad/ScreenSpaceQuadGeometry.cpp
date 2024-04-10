//
// Created by wpsimon09 on 31/12/23.
//

#include "ScreenSpaceQuadGeometry.h"
#include "screenSpaceQuadVertexData.h"
ScreenSpaceQuadGeometry::ScreenSpaceQuadGeometry(std::string name) {
    this->name = "Screen quad";
    this->vao = std::make_unique<VAO>(screenSpaceQuadVertexData, sizeof(screenSpaceQuadVertexData)/sizeof(float), false, true);
    this->numVerticies = 4;
    this->shapes = GL_TRIANGLE_STRIP;
    this->numIndecies = 0;
}
