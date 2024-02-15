//
// Created by wpsimon09 on 06/02/24.
//

#include "FrameBufferDebug.h"

FrameBufferDebug::FrameBufferDebug(int width, int height) : FrameBuffer(width, height) {
    this->shader = new Shader("VertexShader/FrameBufferDebugVertex.glsl" , "FragmentShader/Debug/FrameBufferDebug2.glsl", "Small freme buffer shader");
    this->name = "Small frame buffer";
    this->objectGeometry = new FrameBufferDebugGeometry();
    this->objectMaterial = new BasicMaterialTextured(this->shader, std::move(this->colorAttachment));
}

void FrameBufferDebug::changeTexture(TextureBase texture) {
    delete this->objectMaterial;
    this->objectMaterial = new BasicMaterialTextured(this->shader, std::move(texture));
}
