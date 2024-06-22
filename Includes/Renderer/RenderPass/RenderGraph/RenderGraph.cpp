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
    this->pixelPicking = std::make_unique<PixelPicking>();

    this->postProcessingPass = std::make_unique<PostProcessingPass>();
    this->postProcessingPass->addPostProcessingPass(std::make_unique<ChromaticAberration>());
    this->postProcessingPass->addPostProcessingPass(std::make_unique<Pixelation>());
}

void RenderGraph::preProcessing() {
    auto renderer = this->rendererManager->requestRenderer(shadowMapPass->rendererType);
    if(shadowMapPass->canBeRendered()){
        this->shadowMapPass->render(this->scene, renderer);
    }
    this->renderResults.insert(std::make_pair(SHADOW_MAP_PASS, shadowMapPass->getRenderedResult()));

    renderer = this->rendererManager->requestRenderer(pixelPicking->rendererType);
    if(pixelPicking->canBeRendered()){
        this->pixelPicking->render(this->scene, renderer);
    }
    this->renderResults.insert(std::make_pair(PIXEL_PICKING_PASS, pixelPicking->getRenderedResult()));
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
    auto renderer = this->rendererManager->requestRenderer(postProcessingPass->rendererType);

    if(postProcessingPass->canBeRendered()){
        postProcessingPass->render(scenePass->getRenderedResult(), renderer);
    }
    this->renderResults.insert(std::make_pair(POST_PROCESSING_PASS, postProcessingPass->getRenderedResult()));
}

void RenderGraph::displayResult(FrameBuffer &frameBuffer) {

    RenderPass* finalPass;
    auto allPasses =  this->getRenderPasses();
    for(int i = allPasses.size()-1; i >= 0; i-- ){
        if(allPasses[i].get().canBeRendered()){
            finalPass = &allPasses[i].get();
            break;
        }
    }

    frameBuffer.setColorAttachment(finalPass->getRenderedResult());
    frameBuffer.drawInsideSelf();

    this->renderResults.insert(std::make_pair(FINAL_PASS,finalPass->getRenderedResult()));
}

std::shared_ptr<Texture2D> RenderGraph::getDebugTexture(RENDER_PASS renderPass) {
    return renderResults.find(renderPass)->second;
}

FrameBuffer & RenderGraph::getFrameBuffer(RENDER_PASS render_pass) {
    auto renderPasses = getRenderPasses();
    for(auto renderPass : renderPasses) {
        if(renderPass.get().)
    }
}


void RenderGraph::prepareForNextFrame() {
    this->renderResults.clear();
    this->scenePass->prepareForNextFrame();
    this->shadowMapPass->prepareForNextFrame();
    this->postProcessingPass->prepareForNextFrame();
    this->pixelPicking->prepareForNextFrame();
    //this is not supposed to be here as light is not part of the render graph but this is the only method that is preparing scene for next frame so it is what it is
    auto lightStart = scene->lights.begin();
    while(lightStart != scene->lights.end()){
        lightStart->second->prepareForNextFrame();
        lightStart++;
    }
}

std::vector<std::reference_wrapper<RenderPass>> RenderGraph::getRenderPasses() {
    std::vector<std::reference_wrapper<RenderPass>> renderPasses;
    renderPasses.emplace_back(*shadowMapPass);
    renderPasses.emplace_back(*pixelPicking);
    renderPasses.emplace_back(*scenePass);
    for (auto &postProcessPass : this->postProcessingPass->getChilder()) {
        renderPasses.emplace_back(postProcessPass);
    }

    return renderPasses;
}
