//
// Created by wpsimon09 on 24/03/24.
//

#include "RenderPass.h"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"
#include "imgui/imgui.h"

RenderPass::RenderPass() {
    this->renderPassResult = std::make_shared<Texture2D>(GLFWHelper::getScreenWidth(), GLFWHelper::getScreenHeight(), GL_RGBA16F);
}

void RenderPass::addInput(std::shared_ptr<TextureBase> input) {
    this->inputs.push_back(input);

}

void RenderPass::prepareForNextFrame() {
    this->inputs.clear();
}
