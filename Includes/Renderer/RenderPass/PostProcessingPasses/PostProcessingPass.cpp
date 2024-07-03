//
// Created by wpsimon09 on 19/05/24.
//

#include "PostProcessingPass.h"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"


PostProcessingPass::PostProcessingPass() {
    this->frameBuffer = std::make_unique<FrameBuffer>(GLFWHelper::getScreenWidth(), GLFWHelper::getScreenHeight());
    this->rendererType = POST_PROCESSING;
    this->isPostProcessingPass = true;
    this->name = "Post Processing";
    this->render_pass = POST_PROCESSING_PASS;
}

std::shared_ptr<Texture2D>
PostProcessingPass::render(std::shared_ptr<Texture2D> renderedScene, std::shared_ptr<Renderer> renderer) {
    this->renderPassResult = renderedScene;
    for(auto &postProcessPass: this->postProcessingPasses){
        if(postProcessPass->canBeRendered()){
            this->renderPassResult = postProcessPass->render(this->renderPassResult, renderer);
        }
    }
    return this->renderPassResult;
}

void PostProcessingPass::renderUI() {
        for (auto &postProcessPass: this->postProcessingPasses) {
            postProcessPass->renderUI();
        }
}

void PostProcessingPass::addPostProcessingPass(std::unique_ptr<RenderPass> renderPass) {
    if (renderPass->isPostProcess() && renderPass != nullptr){
        this->postProcessingPasses.emplace_back(std::move(renderPass));
    }else
        std::cerr<<"Invalid post processing render pass";
}

void PostProcessingPass::prepareForNextFrame() {
    for(auto &postProcess: this->postProcessingPasses){
        postProcess->prepareForNextFrame();
    }
}

std::vector<std::reference_wrapper<RenderPass>> PostProcessingPass::getChilder() {
    std::vector<std::reference_wrapper<RenderPass>> children;
    for(auto &postProcess: this->postProcessingPasses){
        children.emplace_back(*postProcess);
    }
    return children;
}

