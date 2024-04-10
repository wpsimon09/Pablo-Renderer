//
// Created by wpsimon09 on 09/04/24.
//


#include "RenderGraph.h"

RenderGraph::RenderGraph(std::shared_ptr<Scene> scene) {
    this->scene = scene;
    this->rendererManager = std::make_unique<RendererManager>();
}

void RenderGraph::init() {
    this->scenePass = std::make_unique<ScenePass>();
    this->shadowMapPass = std::make_unique<ShadowMapPass>();
}

void RenderGraph::preProcessing() {
    auto renderer = this->rendererManager->requestRenderer(shadowMapPass->rendererType);
    this->shadowMapPass->render(this->scene, renderer);
    this->renderResults.insert({"ShadowMapPass", shadowMapPass->getRenderedResult()});
}

void RenderGraph::render() {
    this->scenePass->addInput(shadowMapPass->getRenderedResult());
    auto renderer = this->rendererManager->requestRenderer(scenePass->rendererType);
    this->scenePass->render(scene, renderer);
    this->renderResults.insert({"ScenePass", scenePass->getRenderedResult()});

}

void RenderGraph::displayResult(FrameBuffer &frameBuffer) {
    frameBuffer.setColorAttachment(this->scenePass->getRenderedResult());
    frameBuffer.dispalyOnScreen();
}

std::shared_ptr<Texture2D> RenderGraph::getDebugTexture(std::string renderPassResult) {
    return renderResults.find(renderPassResult)->second;
}

void RenderGraph::postProcessing() {

}
