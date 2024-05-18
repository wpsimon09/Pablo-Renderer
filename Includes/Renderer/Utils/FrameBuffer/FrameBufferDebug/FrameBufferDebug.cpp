//
// Created by wpsimon09 on 06/02/24.
//

#include "FrameBufferDebug.h"

FrameBufferDebug::FrameBufferDebug(int width, int height) : FrameBuffer(width, height) {
    this->shader = ShaderManager::getShader(SHADER_SMALL_FRAME_BUFFER);
    this->name = "Small frame buffer";
    this->objectGeometry = std::make_unique<FrameBufferDebugGeometry>();
    //this->objectGeometry = std::make_unique<ScreenSpaceQuadGeometry>();
    this->objectMaterial = std::make_unique<BasicMaterialTextured>(this->shader, *this->colorAttachment);
}

void FrameBufferDebug::changeTexture(TextureBase texture) {
    this->objectMaterial = std::make_unique<BasicMaterialTextured>(this->shader, std::move(texture));
}
