//
// Created by wpsimon09 on 03/07/24.
//

#include "ScreenSpaceReflection.h"

#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"

ScreenSpaceReflection::ScreenSpaceReflection() {
    auto shader = ShaderManager::getShader(SHADER_SCREEN_SPACE_REFLECTIONS);
    this->frameBuffer =  std::make_unique<FrameBuffer>(GLFWHelper::getScreenWidth(),GLFWHelper::getScreenHeight(),std::move(shader));

    shader = ShaderManager::getShader(SHADER_SCREEN_SPACE_REFLECTIONS_COLOUR_SAMPLING);
    this->mergeFrameBufer= std::make_unique<FrameBuffer>(GLFWHelper::getScreenWidth(),GLFWHelper::getScreenHeight(),std::move(shader));

    this->isActive = true;
    this->isPostProcessingPass = true;

    this->rendererType = POST_PROCESSING;
    this->render_pass = SCREEN_SPACE_REFLECTION_PASS;
    this->name = "Screen space reflection pass";
}

std::shared_ptr<Texture2D> ScreenSpaceReflection::render(std::shared_ptr<Texture2D> renderedScene,
                                                         std::shared_ptr<Renderer> renderer) {
    //getting ray traced SSR
    renderer->setInputsForRenderPass(PabloRenderer::getInstance()->getRenderGraph().getRenderPass(SCENE_PASS).get().getAdditionalOutputs());

    auto shader = frameBuffer->getShader();
    shader->use();

    shader->setMat4("Projection", PabloRenderer::getInstance()->getScene()->camera->getPojectionMatix());
    shader->setMat4("invProjection", glm::inverse(PabloRenderer::getInstance()->getScene()->camera->getPojectionMatix()));

    shader->setMat4("View", PabloRenderer::getInstance()->getScene()->camera->getViewMatrix());
    shader->setMat4("invView", glm::inverse(PabloRenderer::getInstance()->getScene()->camera->getViewMatrix()));

    shader->setVec3("cameraPosition", PabloRenderer::getInstance()->getScene()->camera->getPosition());

    renderer->render(this->frameBuffer);
    this->renderPassResult = this->frameBuffer->getRenderedResult();

    renderer->clearInputs();
    this->renderPassResult->shaderName = "SSR";

    //gettingFinalResult
    renderedScene->shaderName = "renderedScene";
    renderer->setInputsForRenderPass({this->renderPassResult, renderedScene});
    renderer->render(this->mergeFrameBufer);
    this->renderPassResult = this->mergeFrameBufer->getRenderedResult();
    return this->renderPassResult;
}
