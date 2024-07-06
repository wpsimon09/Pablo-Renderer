//
// Created by wpsimon09 on 03/07/24.
//

#include "ScreenSpaceReflection.h"

#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"

ScreenSpaceReflection::ScreenSpaceReflection() {
    auto shader = ShaderManager::getShader(SHADER_SCREEN_SPACE_REFLECTIONS);
    this->frameBuffer =  std::make_unique<FrameBuffer>(GLFWHelper::getScreenWidth(),GLFWHelper::getScreenHeight(),std::move(shader));
    this->isActive = true;
    this->isPostProcessingPass = true;

    this->rendererType = POST_PROCESSING;
    this->render_pass = SCREEN_SPACE_REFLECTION_PASS;
    this->name = "Screen space reflection pass";
}

std::shared_ptr<Texture2D> ScreenSpaceReflection::render(std::shared_ptr<Texture2D> renderedScene,
                                                         std::shared_ptr<Renderer> renderer) {
    renderer->setInputsForRenderPass(PabloRenderer::getInstance()->getRenderGraph().getRenderPass(SCENE_PASS).get().getAdditionalOutputs());
    frameBuffer->getShader()->use();
    renderer->render(this->frameBuffer);
    this->renderPassResult = this->frameBuffer->getRenderedResult();

    return this->renderPassResult;
}
