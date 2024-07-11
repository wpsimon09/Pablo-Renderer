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

    uniformValues["cb_zThickness"] = Parameter(0.2);
    uniformValues["cb_nearPlaneZ"] =Parameter(PabloRenderer::getInstance()->getScene()->camera->getFarPlane());
    uniformValues["cb_farPlaneZ"] = PabloRenderer::getInstance()->getScene()->camera->getNearPlane();
    uniformValues["cb_stride"] = 0.2f;
    uniformValues["cb_maxSteps"] = 20.0f;
    uniformValues["cb_maxDistance"] = 30.0f;
    uniformValues["cb_strideZCutoff"] = 20.0f;
    uniformValues["cb_fadeStart"] = 200.0f;
    uniformValues["cb_fadeEnd"] = 300.0f;
    uniformValues["cb_sslr_padding0"] = 0.2f;
}

std::shared_ptr<Texture2D> ScreenSpaceReflection::render(std::shared_ptr<Texture2D> renderedScene,
                                                         std::shared_ptr<Renderer> renderer) {
    //getting ray traced SSR
    renderer->setInputsForRenderPass(PabloRenderer::getInstance()->getRenderGraph().getRenderPass(SCENE_PASS).get().getAdditionalOutputs());

    auto shader = this->frameBuffer->getShader();
    shader->use();
    shader->setMat4("Projection", PabloRenderer::getInstance()->getScene()->camera->getPojectionMatix());
    shader->setMat4("invProjection", glm::inverse(PabloRenderer::getInstance()->getScene()->camera->getPojectionMatix()));

    shader->setMat4("View", PabloRenderer::getInstance()->getScene()->camera->getViewMatrix());
    shader->setMat4("invView", glm::inverse(PabloRenderer::getInstance()->getScene()->camera->getViewMatrix()));

    setParamsToShader(shader);

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

void ScreenSpaceReflection::setParamsToShader(std::shared_ptr<Shader> shader) {
    shader->use();
    for(auto param: this->uniformValues) {
        shader->setFloat(param.first, param.second);
    }
}

void ScreenSpaceReflection::renderUI() {
    RenderPass::renderUI();
    for(auto param: this->uniformValues) {
        ImGui::SliderFloat(param.first.c_str(), &param.second, 0.0, 100);
    }
}
