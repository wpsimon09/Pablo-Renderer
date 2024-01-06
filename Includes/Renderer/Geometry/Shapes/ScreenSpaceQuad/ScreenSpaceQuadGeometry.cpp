//
// Created by wpsimon09 on 31/12/23.
//

#include "ScreenSpaceQuadGeometry.h"
#include "screenSpaceQuadVertexData.h"
ScreenSpaceQuadGeometry::ScreenSpaceQuadGeometry(std::string name) {
    this->name;
    this->vao = new VAO(screenSpaceQuadVertexData, sizeof(screenSpaceQuadVertexData)/sizeof(float), false, true);
    this->verticies = 4;
    this->shapes = GL_TRIANGLE_STRIP;
    this->indecies = 0;
}
