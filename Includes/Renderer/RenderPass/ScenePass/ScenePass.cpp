//
// Created by wpsimon09 on 24/03/24.
//

#include "ScenePass.h"

ScenePass::ScenePass():RenderPass() {
    this->frameBuffer = std::make_unique<FrameBuffer>(800, 600);
    this->rendererType = COLOR_DEPTH_STENCIL;
}

std::shared_ptr<Texture2D> ScenePass::render(std::shared_ptr<Scene> scene, std::shared_ptr<Renderer> renderer) {
    scene->renderingConstrains = NONE;
    renderer->render(scene, this->frameBuffer);
    this->renderPassResult = this->frameBuffer->getRenderedResult();
    return this->renderPassResult;
}

