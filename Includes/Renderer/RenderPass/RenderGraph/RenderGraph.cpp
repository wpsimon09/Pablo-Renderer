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
    this->renderResults.insert(std::make_pair(SHADOW_MAP_PASS, shadowMapPass->getRenderedResult()));
}

void RenderGraph::render() {
    this->scenePass->addInput(shadowMapPass->getRenderedResult());
    auto renderer = this->rendererManager->requestRenderer(scenePass->rendererType);
    this->scenePass->render(scene, renderer);
    this->renderResults.insert(std::make_pair(SCENE_PASS, scenePass->getRenderedResult()));
}

void RenderGraph::displayResult(FrameBuffer &frameBuffer) {
    frameBuffer.setColorAttachment(this->chromaticAerrationPass->getRenderedResult());
    frameBuffer.drawInsideSelf();
    this->renderResults.insert(std::make_pair(FINAL_PASS, frameBuffer.getRenderedResult()));
}

void RenderGraph::postProcessing() {
    auto renderer = this->rendererManager->requestRenderer(chromaticAerrationPass->rendererType);
    chromaticAerrationPass->render(this->scenePass->getRenderedResult(), renderer);
    this->renderResults.insert(std::make_pair(POST_PROCESSING_CHROMATIC_ABERRATION, chromaticAerrationPass->getRenderedResult()));
}

std::shared_ptr<Texture2D> RenderGraph::getDebugTexture(RENDER_PASS renderPass) {
    return renderResults.find(renderPass)->second;
}


void RenderGraph::prepareForNextFrame() {
    this->renderResults.clear();
    this->scenePass->prepareForNextFrame();
    this->shadowMapPass->prepareForNextFrame();
    this->chromaticAerrationPass->prepareForNextFrame();

    auto lightStart = scene->lights.begin();
    while(lightStart != scene->lights.end()){
        lightStart->second->prepareForNextFrame();
        lightStart++;
    }
}
