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

    renderer->render(this->frameBuffer);

    this->renderPassResult = this->frameBuffer->getRenderedResult();
    return this->renderPassResult;
}
