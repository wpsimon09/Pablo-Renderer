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


    uniformValues["ReflectionVecScale"] = Parameter<float>(400, true, 50.0f,400.0f);
    uniformValues["MaxSamplerCount"] = Parameter<float>(140, true, 0.0f,400.0f);
    uniformValues["MaxMarchStep"] = Parameter<float>(0.37, true, 0.0f,2.0f);
    uniformValues["MaxBinarySearchSteps"] = Parameter<float>(6.0, true, 0.0f,400.0f);
    uniformValues["MidRaySampleWeight"] = Parameter<float>(0.5, true, 0.0f,4.0f);
    uniformValues["MaxDistance"] = Parameter<float>(36, true, 1.0f,100.0f);



    /*
    uniformValues["minRayStep"] = Parameter<float>(0.01f, true, 0.0f,10.0f);
    uniformValues["maxSteps"] = Parameter<float>(40.0f, true, 0.0f,200.0f);
    uniformValues["numBinarySearchSteps"] = Parameter<float>(20.0f, true, 0.0f,200.0f);
    uniformValues["reflectionSpecularFalloffExponent"] = Parameter<float>(2.2f, true, 0.0f,10.0f);
    uniformValues["step"] = Parameter<float>(2.2f, true, 0.0f,10.0f);
    */


    /*
    uniformValues["cb_zThickness"] = Parameter(0.2f);
    uniformValues["cb_nearPlaneZ"] =Parameter<float>(PabloRenderer::getInstance()->getScene()->camera->getNearPlane(), false);
    uniformValues["cb_farPlaneZ"] = Parameter<float>(PabloRenderer::getInstance()->getScene()->camera->getFarPlane(), false);
    uniformValues["cb_maxSteps"] = Parameter<float>(10.0f, true, 0.0f, 200.0f)  ;
    uniformValues["cb_maxDistance"] = Parameter<float>(0.2f, true, 0.0f, 2000.0f);
    uniformValues["cb_strideZCutoff"] = Parameter<float>(30.0f, true, 0.0f, 100.0f);
    uniformValues["cb_fadeStart"] = Parameter<float>(200.0f, true, 0.0f, 400.0f);
    uniformValues["cb_fadeEnd"] = Parameter<float>(300.0f, true, 0.0f, 400.0f);
    uniformValues["cb_sslr_padding0"] = Parameter<float>(0.2f);*/
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

    //this->renderPassResult = renderer->blur(this->renderPassResult, this->blurIntensity);
    this->renderPassResult->shaderName = "ssr";
    renderer->clearInputs();

    //gettingFinalResult
    renderedScene->shaderName = "renderedScene";
    renderer->setInputsForRenderPass(PabloRenderer::getInstance()->getRenderGraph().getRenderPass(SCENE_PASS).get().getAdditionalOutputs());
    renderer->addInput(this->renderPassResult);
    renderer->addInput(renderedScene);

    renderer->render(this->mergeFrameBufer);
    this->renderPassResult = this->mergeFrameBufer->getRenderedResult();
    this->renderPassResult = renderer->blur(renderPassResult, this->blurIntensity);
    return this->renderPassResult;
}

void ScreenSpaceReflection::setParamsToShader(std::shared_ptr<Shader> shader) {
    shader->use();
    for(auto param: this->uniformValues) {
        shader->setFloat(param.first, param.second.getValueConst());
    }
}

void ScreenSpaceReflection::renderUI() {
    RenderPass::renderUI();
    for(auto &param: this->uniformValues) {
        if(param.second.canBeChanged())
            ImGui::SliderFloat(param.first.c_str(), &param.second.getValue(), param.second.getMin(), param.second.getMax());
        else {
            std::string s = param.first + ":" + std::to_string(param.second.getValue());
            ImGui::BulletText(s.c_str());
        }
    }
    ImGui::SeparatorText("Blur intenstiy");
    ImGui::SliderInt("Blur", &this->blurIntensity, 0,30);
}