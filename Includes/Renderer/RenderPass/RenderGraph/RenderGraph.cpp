//
// Created by wpsimon09 on 09/04/24.
//


#include "RenderGraph.h"

RenderGraph::RenderGraph(std::shared_ptr<Scene> scene) {
    this->scene = scene;
}

void RenderGraph::init() {
    this->renderPasses.insert({"ShadowMapPass", std::make_unique<ShadowMapPass>()});
    this->renderPasses.insert({"ScenePass", std::make_unique<ScenePass>()});
}

void RenderGraph::build() {
    //TODO implement
}

void RenderGraph::render() {
    auto currentRenderPass = renderPasses.begin();
    while(currentRenderPass != renderPasses.end()){
        auto responseRenderer = rendererManager->requestRenderer(currentRenderPass->second->rendererType);
        currentRenderPass->second->render(this->scene, responseRenderer);
        currentRenderPass++;
    }
}

void RenderGraph::displayResult(FrameBuffer &frameBuffer) {
    frameBuffer.setColorAttachment(this->renderPasses.find("ScenePass")->second->getRenderedResult());
    frameBuffer.dispalyOnScreen();
}

std::shared_ptr<Texture2D> RenderGraph::getDebugTexture(std::string renderPassResult) {
    return renderPasses.find(renderPassResult)->second->getRenderedResult();
}
