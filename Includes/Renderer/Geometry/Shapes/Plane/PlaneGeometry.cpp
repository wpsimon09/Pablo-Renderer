//
// Created by wpsimon09 on 30/12/23.
//

#include "PlaneGeometry.h"

#include <utility>
#include "planeVertexData.h"
PlaneGeometry::PlaneGeometry(std::string name): Geometry() {
    this->name = std::move(name);
    this->vao = new VAO(planeVertexData, sizeof(planeVertexData)/sizeof(float));
}
