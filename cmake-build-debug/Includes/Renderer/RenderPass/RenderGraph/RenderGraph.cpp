//
// Created by wpsimon09 on 09/04/24.
//


#include "RenderGraph.h"

RenderGraph::RenderGraph(std::shared_ptr<Scene> scene) {
    this->scene = scene;
    this->rendererManager = std::make_unique<RendererManager>();
}

void RenderGraph::init() {
    this->renderPasses.insert({"ShadowMapPass", std::make_unique<ShadowMapPass>()});
    this->renderPasses.insert({"ScenePass", std::make_unique<ScenePass>()});

    this->scenePass = std::make_unique<ScenePass>();

    this->shadowMapPass = std::make_unique<ShadowMapPass>();
}

void RenderGraph::preProcessing() {
    auto renderer = this->rendererManager->requestRenderer(shadowMapPass->rendererType);
    this->shadowMapPass->render(this->scene, renderer);
}

void RenderGraph::render() {
    this->scenePass->addInput(shadowMapPass->getRenderedResult());
    auto renderer = this->rendererManager->requestRenderer(scenePass->rendererType);
    this->scenePass->render(scene, renderer);
}

void RenderGraph::displayResult(FrameBuffer &frameBuffer) {
    frameBuffer.setColorAttachment(this->renderPasses.find("ScenePass")->second->getRenderedResult());
    frameBuffer.dispalyOnScreen();
}

std::shared_ptr<Texture2D> RenderGraph::getDebugTexture(std::string renderPassResult) {
    return renderPasses.find(renderPassResult)->second->getRenderedResult();
}

void RenderGraph::postProcessing() {

}
