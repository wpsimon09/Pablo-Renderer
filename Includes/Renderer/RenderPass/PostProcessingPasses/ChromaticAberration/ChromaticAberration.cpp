//
// Created by wpsimon09 on 12/05/24.
//

#include "ChromaticAberration.h"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"


ChromaticAberration::ChromaticAberration() {
    auto shader = ShaderManager::getShader(SHADER_CHROMATIC_ABBERATION);
    this->frameBuffer = std::make_unique<FrameBuffer>(GLFWHelper::getScreenWidth(),GLFWHelper::getScreenHeight(),std::move(shader));
    this->rendererType = POST_PROCESSING;
    this->render_pass = CHROMATIC_ABBERATION_POST_PROCESSING_PASS;
    this->isPostProcessingPass = true;
    this->isActive = false;

    this->name = "Chromatic aberration";
}

std::shared_ptr<Texture2D>
ChromaticAberration::render(std::shared_ptr<Texture2D> renderedScene, std::shared_ptr<Renderer> renderer) {
    renderedScene->shaderName = "sceneResult";
    this->inputs.emplace_back(renderedScene);

    renderer->setInputsForRenderPass(this->inputs);
    renderer->render(this->frameBuffer);

    this->renderPassResult = this->frameBuffer->getRenderedResult();
    return this->renderPassResult;
}
