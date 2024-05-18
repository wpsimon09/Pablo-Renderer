//
// Created by wpsimon09 on 15/05/24.
//

#include "Pixelation.h"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"


Pixelation::Pixelation() {
    auto shader  = ShaderManager::getShader(SHADER_PIXELATION);
    this->frameBuffer = std::make_unique<FrameBuffer>(GLFWHelper::getScreenWidth(),GLFWHelper::getScreenHeight(),std::move(shader));
    this->rendererType = POST_PROCESSING;
    this->isPostProcessingPass = true;

    this->name = "Pixelation pass";
}

std::shared_ptr<Texture2D>
Pixelation::render(std::shared_ptr<Texture2D> renderedScene, std::shared_ptr<Renderer> renderer) {
    renderedScene->shaderName = "sceneResult";
    this->inputs.emplace_back(renderedScene);


    this->frameBuffer->getShader()->use();
    this->frameBuffer->getShader()->setInt("pixelSize", this->pixelSize);

    renderer->setInputsForRenderPass(this->inputs);
    renderer->render(this->frameBuffer);

    this->renderPassResult = this->frameBuffer->getRenderedResult();
    return this->renderPassResult;
}

void Pixelation::renderUI() {
    RenderPass::renderUI();
    ImGui::SliderInt("Pixelation", &this->pixelSize,1, 20);
}
