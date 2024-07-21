//
// Created by wpsimon09 on 21/07/24.
//

#include "ConeTracingPass.h"

#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"

ConeTracingPass::ConeTracingPass() {
    auto shader = ShaderManager::getShader(SHADER_SSR_CONE_TRACING);
    this->frameBuffer = std::make_unique<FrameBuffer>(GLFWHelper::getScreenWidth(), GLFWHelper::getScreenHeight(),std::move(shader), nullptr, false, 0, false);
    this->rendererType = POST_PROCESSING;
    this->isPostProcessingPass = true;
    this->render_pass = SCREEN_SPACE_CONE_TRACING;
    this->name = "Screen space cone tracing";
    this->isActive = true;
}

void ConeTracingPass::renderUI() {
    RenderPass::renderUI();
}

std::shared_ptr<Texture2D> ConeTracingPass::render(std::shared_ptr<Texture2D> renderedScene,
    std::shared_ptr<Renderer> renderer) {

    auto gBuffers = PabloRenderer::getInstance()->getRenderGraph().getRenderPass(SCENE_PASS).get().getAdditionalOutputs();
    auto RayTracingBuffer = PabloRenderer::getInstance()->getRenderGraph().getRenderPass(SCREEN_SPACE_REFLECTION_PASS).get().getRenderedResult();
    RayTracingBuffer->shaderName = "RayTracingBuffer";

    auto ConvolvedScene = PabloRenderer::getInstance()->getRenderGraph().getRenderPass(SCENE_CONVOLUTION_PASS).get().getRenderedResult();;
    ConvolvedScene->shaderName = "ConvolvedScene";

    renderer->setInputsForRenderPass(gBuffers);
    renderer->addInput(RayTracingBuffer);
    renderer->addInput(ConvolvedScene);

    renderer->render(this->frameBuffer);

    this->renderPassResult = this->frameBuffer->getRenderedResult();
    return this->renderPassResult;
}
