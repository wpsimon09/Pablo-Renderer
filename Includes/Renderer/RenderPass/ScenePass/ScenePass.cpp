//
// Created by wpsimon09 on 24/03/24.
//

#include "ScenePass.h"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"

ScenePass::ScenePass():RenderPass() {
    glm::vec2 screenDimentions = GLFWHelper::getScreenDimensions();
    this->gNormal = std::make_shared<Texture2D>(screenDimentions.x, screenDimentions.y, GL_RGBA16F);
    this->gPosition = std::make_shared<Texture2D>(screenDimentions.x, screenDimentions.y, GL_RGBA16F);
    this->gColourAndShininess = std::make_shared<Texture2D>(screenDimentions.x, screenDimentions.y, GL_RGBA16F);

    this->frameBuffer = std::make_unique<FrameBuffer>(GLFWHelper::getScreenWidth(),GLFWHelper::getScreenHeight());

    this->frameBuffer->transferToGbufferSupport(gPosition, gNormal,gColourAndShininess);

    this->rendererType = COLOR_DEPTH_STENCIL;
    this->render_pass = SCENE_PASS;
    this->name = "Scene pass";
}

std::shared_ptr<Texture2D> ScenePass::render(std::shared_ptr<Scene> scene, std::shared_ptr<Renderer> renderer) {
    scene->renderingConstrains = NONE;
    renderer->setInputsForRenderPass(this->inputs);
    renderer->render(scene, this->frameBuffer);
    this->renderPassResult = this->frameBuffer->getRenderedResult();
    return this->renderPassResult;
}

