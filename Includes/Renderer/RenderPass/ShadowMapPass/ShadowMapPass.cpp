//
// Created by wpsimon09 on 30/03/24.
//

#include "ShadowMapPass.h"


ShadowMapPass::ShadowMapPass() {
    this->frameBuffer = std::make_unique<FrameBuffer>(1200, 800);
    this->frameBuffer->makeDepthOnly();
    this->rendererType = DEPTH_ONLY;
    this->name = "Shadow map pass";
}

std::shared_ptr<Texture2D> ShadowMapPass::render(std::shared_ptr<Scene> scene, std::shared_ptr<Renderer> renderer) {
    scene->renderingConstrains = SHADOW_ONLY;
    renderer->render(scene, this->frameBuffer);
    this->renderPassResult = frameBuffer->getRenderedResult();
    this->renderPassResult->shaderName = "shadowMap";
    return this->renderPassResult;
}
