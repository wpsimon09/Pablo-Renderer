//
// Created by wpsimon09 on 15/02/24.
//

#include "BaseStage.h"


BaseStage::BaseStage(int width, int height, Shader* shader , Geometry* geometry) {
    this->shader = shader;
    this->geometry = geometry;
    this->frameBuffer = new FrameBuffer(width, height);
    this->frameBuffer->setShader(shader);
    this->frameBuffer
}
