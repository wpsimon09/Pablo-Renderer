//
// Created by wpsimon09 on 19/05/24.
//

#include "PostProcessingPass.h"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"


PostProcessingPass::PostProcessingPass() {
    auto shader = ShaderManager::getShader(SHADER_POST_PROCESSING_MERGER);

    this->frameBuffer = std::make_unique<FrameBuffer>(GLFWHelper::getScreenWidth(), GLFWHelper::getScreenHeight(), std::move(shader));
    this->rendererType = POST_PROCESSING;
    this->isPostProcessingPass = true;
}

std::shared_ptr<Texture2D>
PostProcessingPass::render(std::shared_ptr<Texture2D> renderedScene, std::shared_ptr<Renderer> renderer) {
    return RenderPass::render(renderedScene, renderer);
}

void PostProcessingPass::renderUI() {
    RenderPass::renderUI();;
}

void PostProcessingPass::addPostProcessingPass(std::unique_ptr<RenderPass> renderPass) {
    if (renderPass->isPostProcess() && renderPass != nullptr){
        this->postProcessingPasses.emplace_back(std::move(renderPass));
    }else
        std::cerr<<"Invalid post processing render pass supported ";
}
