//
// Created by wpsimon09 on 03/07/24.
//

#include "ScreenSpaceReflection.h"

#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"

ScreenSpaceReflection::ScreenSpaceReflection() {
    auto shader = ShaderManager::getShader(SHADER_SCREEN_SPACE_REFLECTIONS);
    this->reflectedUVcoordinatesFrameBuffe =  std::make_unique<FrameBuffer>(GLFWHelper::getScreenWidth(),GLFWHelper::getScreenHeight(),std::move(shader));

    shader = ShaderManager::getShader(SHADER_SCREEN_SPACE_REFLECTIONS_COLOUR_SAMPLING);
    this->reflectedColourFrameBuffer = std::make_unique<FrameBuffer>(GLFWHelper::getScreenWidth(),GLFWHelper::getScreenHeight(),std::move(shader));

    this->isActive = true;
    this->isPostProcessingPass = true;

    this->rendererType = POST_PROCESSING;
    this->render_pass = SCREEN_SPACE_REFLECTION_PASS;
    this->name = "Screen space reflection pass";
}

std::shared_ptr<Texture2D> ScreenSpaceReflection::render(std::shared_ptr<Texture2D> renderedScene,
                                                         std::shared_ptr<Renderer> renderer) {
    //getting reflected UV coordinates
    renderer->setInputsForRenderPass(PabloRenderer::getInstance()->getRenderGraph().getRenderPass(SCENE_PASS).get().getAdditionalOutputs());
    renderer->render(this->reflectedUVcoordinatesFrameBuffe);

    auto UVTexture = this->reflectedUVcoordinatesFrameBuffe->getRenderedResult();
    UVTexture->shaderName = "reflectedUVCoordinatesMap";

    auto frameColor = PabloRenderer::getInstance()->getRenderGraph().getRenderPass(SCENE_PASS).get().getRenderedResult();
    frameColor->shaderName = "colourTexture";
    //getting reflected colour
    std::vector<std::shared_ptr<TextureBase>> inputsForSpecularMapPass = {UVTexture, frameColor};

    renderer->setInputsForRenderPass(inputsForSpecularMapPass);
    renderer->render(this->reflectedColourFrameBuffer);
    this->renderPassResult = this->reflectedColourFrameBuffer->getRenderedResult();

    return this->renderPassResult;
}
