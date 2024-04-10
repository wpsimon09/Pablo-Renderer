//
// Created by wpsimon09 on 24/03/24.
//

#include "RenderPass.h"

RenderPass::RenderPass() {
    this->renderPassResult = std::make_shared<Texture2D>(800, 600, GL_RGBA16F);
}

void RenderPass::addInput(std::shared_ptr<TextureBase> input) {
    this->inputs.push_back(input);
}

void RenderPass::prepareForNextFrame() {
    this->inputs.clear();
}
