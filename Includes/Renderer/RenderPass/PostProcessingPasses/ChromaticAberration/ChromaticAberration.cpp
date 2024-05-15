//
// Created by wpsimon09 on 12/05/24.
//

#include "ChromaticAberration.h"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"


ChromaticAberration::ChromaticAberration() {
    auto shader = std::make_shared<Shader>("VertexShader/FrameBufferDebugVertex.glsl" , "FragmentShader/Postprocessing/ChromaticAbriviationFragment.glsl", "ChromaticAbbriviationShader");
    this->frameBuffer = std::make_unique<FrameBuffer>(GLFWHelper::getScreenWidth(),GLFWHelper::getScreenHeight(),std::move(shader));
    this->rendererType = POST_PROCESSING;
    this->isPostProcessingPass = true;

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
