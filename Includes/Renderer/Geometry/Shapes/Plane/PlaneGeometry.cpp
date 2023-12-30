//
// Created by wpsimon09 on 30/12/23.
//

#include "PlaneGeometry.h"
#include "planeVertexData.h"
PlaneGeometry::PlaneGeometry(std::string nsme) {
    this->vao = new VAO(planeVertexData, sizeof(planeVertexData)/sizeof(float));
}
