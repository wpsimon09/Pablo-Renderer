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
    this->name = "Post Processing";
}

std::shared_ptr<Texture2D>
PostProcessingPass::render(std::shared_ptr<Texture2D> renderedScene, std::shared_ptr<Renderer> renderer) {
    int i = 0;
    for(auto &postProcessPass: this->postProcessingPasses){
        if(postProcessPass->canBeRendered()){
            auto outcome = postProcessPass->render(renderedScene, renderer);
            outcome->shaderName = "postProcessingEffect["+std::to_string(i) +"]";
            this->addInput(outcome);
        }
        i++;
    }
    renderer->setInputsForRenderPass(this->inputs);
    renderer->render(this->frameBuffer);

    this->renderPassResult = this->frameBuffer->getRenderedResult();

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
        std::cerr<<"Invalid post processing render pass supported ";
}

void PostProcessingPass::prepareForNextFrame() {
    for(auto &postProcess: this->postProcessingPasses){
        postProcess->prepareForNextFrame();
    }
}

