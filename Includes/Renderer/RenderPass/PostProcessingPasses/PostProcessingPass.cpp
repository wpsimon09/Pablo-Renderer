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
    for(auto &postProcessPass: this->postProcessingPasses){
        if(postProcessPass->canBeRendered()){
            this->mergePasses(postProcessPass->render(renderedScene, renderer));
        }else
            continue;
    }
    return this->renderPassResult;
}

void PostProcessingPass::renderUI() {
    if(ImGui::TreeNodeEx("Post processing passes")){
        for (auto &postProcessPass: this->postProcessingPasses) {
            postProcessPass->renderUI();
        }
        ImGui::TreePop();
    }
}

void PostProcessingPass::addPostProcessingPass(std::unique_ptr<RenderPass> renderPass) {
    if (renderPass->isPostProcess() && renderPass != nullptr){
        this->postProcessingPasses.emplace_back(std::move(renderPass));
    }else
        std::cerr<<"Invalid post processing render pass supported ";
}

void PostProcessingPass::mergePasses(std::shared_ptr<Texture2D> passToMerge) {
    if(renderPassResult != nullptr){
        this->renderPassResult->shaderName = "previousResult";
        this->renderPassResult->setSamplerID(0);

        passToMerge->shaderName = "newResult";
        passToMerge->setSamplerID(1);

        auto mergeShader = frameBuffer->getShader();
        ShaderHelper::setTextureToShader(mergeShader,*renderPassResult, renderPassResult->shaderName);
        ShaderHelper::setTextureToShader(mergeShader,*passToMerge, passToMerge->shaderName);

        frameBuffer->drawInsideSelf(false);

        this->renderPassResult = frameBuffer->getRenderedResult();
    }
    else{
        this->renderPassResult = passToMerge;
    }
}

