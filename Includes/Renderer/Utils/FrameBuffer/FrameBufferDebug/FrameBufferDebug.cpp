//
// Created by wpsimon09 on 06/02/24.
//

#include "FrameBufferDebug.h"

FrameBufferDebug::FrameBufferDebug(int width, int height) : FrameBuffer(width, height) {
    this->shader = new Shader("VertexShader/FrameBufferDebugVertex.glsl" , "FragmentShader/FrameBufferDebugFragment.glsl", "FrameBufferDebug shader");
    this->objectGeometry = new FrameBufferDebugGeometry();
}
