//
// Created by wpsimon09 on 18/07/24.
//

#include "SceneImageConvolutionPass.h"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"

SceneImageConvolutionPass::SceneImageConvolutionPass() {
    this->frameBuffer = std::make_unique<FrameBuffer>(GLFWHelper::getScreenWidth(),GLFWHelper::getScreenHeight());
    this->rendererType = POST_PROCESSING;
    this->isPostProcessingPass = true;
    this->render_pass = SCENE_CONVOLUTION_PASS;
    this->name = "Scene convolution pass";
    this->isActive = true;
}

std::shared_ptr<Texture2D> SceneImageConvolutionPass::render(std::shared_ptr<Texture2D> renderedScene, std::shared_ptr<Renderer> renderer) {
    renderedScene->shaderName = "sceneResults";
    this->inputs.emplace_back(renderedScene);

    renderer->setInputsForRenderPass(this->inputs);
    renderer->blurToMipMaps(renderedScene, 6);
}
