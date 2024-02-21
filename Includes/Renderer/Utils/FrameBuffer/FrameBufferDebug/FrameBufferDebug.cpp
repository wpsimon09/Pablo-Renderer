//
// Created by wpsimon09 on 06/02/24.
//

#include "FrameBufferDebug.h"

FrameBufferDebug::FrameBufferDebug(int width, int height) : FrameBuffer(width, height) {
    this->shader = std::make_unique<Shader>("VertexShader/FrameBufferDebugVertex.glsl" , "FragmentShader/Debug/FrameBufferDebug2.glsl", "Small freme buffer shader");
    this->name = "Small frame buffer";
    this->objectGeometry = std::make_unique<FrameBufferDebugGeometry>();
    this->objectMaterial = std::make_unique<BasicMaterialTextured>(std::move(this->shader), *this->colorAttachment);
}

void FrameBufferDebug::changeTexture(TextureBase texture) {
    this->objectMaterial = std::make_unique<BasicMaterialTextured>(std::move(this->shader), std::move(texture));
}
