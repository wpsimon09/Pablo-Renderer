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
    this->chromaticAerrationPass = std::make_unique<ChromaticAberration>();
}

void RenderGraph::preProcessing() {
    auto renderer = this->rendererManager->requestRenderer(shadowMapPass->rendererType);
    if(shadowMapPass->canBeRendered()){
        this->shadowMapPass->render(this->scene, renderer);
    }
    this->renderResults.insert(std::make_pair(SHADOW_MAP_PASS, shadowMapPass->getRenderedResult()));
}

void RenderGraph::render() {
    this->scenePass->addInput(shadowMapPass->getRenderedResult());
    auto renderer = this->rendererManager->requestRenderer(scenePass->rendererType);
    if(scenePass->canBeRendered()){
        this->scenePass->render(scene, renderer);
    }
    this->renderResults.insert(std::make_pair(SCENE_PASS, scenePass->getRenderedResult()));
}

void RenderGraph::postProcessing() {
    auto renderer = this->rendererManager->requestRenderer(chromaticAerrationPass->rendererType);
    if(chromaticAerrationPass->canBeRendered()){
        chromaticAerrationPass->render(this->scenePass->getRenderedResult(), renderer);
    }
    this->renderResults.insert(std::make_pair(POST_PROCESSING_CHROMATIC_ABERRATION, chromaticAerrationPass->getRenderedResult()));
}

void RenderGraph::displayResult(FrameBuffer &frameBuffer) {

    RenderPass* finalPass;
    auto allPasses =  this->getRenderPasses();
    for(auto &pass: allPasses){
        if(pass.get().canBeRendered()){
            finalPass = &pass.get();
        }
    }
    frameBuffer.setColorAttachment(finalPass->getRenderedResult());
    frameBuffer.drawInsideSelf();

    this->renderResults.insert(std::make_pair(FINAL_PASS, frameBuffer.getRenderedResult()));
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

std::vector<std::reference_wrapper<RenderPass>> RenderGraph::getRenderPasses() {
    std::vector<std::reference_wrapper<RenderPass>> renderPasses;
    renderPasses.emplace_back(*shadowMapPass);
    renderPasses.emplace_back(*scenePass);
    renderPasses.emplace_back(*chromaticAerrationPass);
    return renderPasses;
}
