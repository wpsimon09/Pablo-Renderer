//
// Created by wpsimon09 on 06/02/24.
//

#include "FrameBufferDebugGeometry.h"
#include "debugFrameBufferPlaneData.h"
FrameBufferDebugGeometry::FrameBufferDebugGeometry(): Geometry() {
    this->name;
    this->vao = std::make_unique<VAO>(frameBufferDebugPlane, sizeof(frameBufferDebugPlane)/sizeof(float), false, true);
    this->numVerticies = 6;
    this->shapes = GL_TRIANGLES;
    this->numIndecies = 0;
}
