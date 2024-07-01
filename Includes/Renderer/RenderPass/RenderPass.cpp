//
// Created by wpsimon09 on 24/03/24.
//

#include "RenderPass.h"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"
#include "Renderer/UI/Components/RenderableCreateationUI/FIleWindowUI/FileWindowUI.h"

RenderPass::RenderPass() {
    this->renderPassResult = std::make_shared<Texture2D>(GLFWHelper::getScreenWidth(), GLFWHelper::getScreenHeight(), GL_RGBA16F);
}

void RenderPass::addInput(std::shared_ptr<TextureBase> input) {
    this->inputs.push_back(input);

}

void RenderPass::prepareForNextFrame() {
    this->inputs.clear();
}

void RenderPass::renderUI() {
    ImGui::Text("Result of render pass");
    ImGui::Checkbox("Is active", &isActive);
    ImVec2 imageSize((float) this->renderPassResult->texWidth/4, (float) this->renderPassResult->texHeight/4);
    ImGui::Image(reinterpret_cast<ImTextureID>(this->renderPassResult->ID), imageSize, ImVec2(0, 1),ImVec2(1, 0));

    if(ImGui::Button("Take a photo")){
        this->frameBuffer->saveAsPNG("image.png");
    }
}

FrameBuffer & RenderPass::getFrameBuffer() {
    return *this->frameBuffer;
}
