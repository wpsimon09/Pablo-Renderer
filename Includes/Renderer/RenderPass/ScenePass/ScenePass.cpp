//
// Created by wpsimon09 on 24/03/24.
//

#include "ScenePass.h"

ScenePass::ScenePass():RenderPass() {
    this->frameBuffer = std::make_unique<FrameBuffer>(800, 600);
    this->name = "scene pass";
}

std::shared_ptr<Texture2D> ScenePass::render(std::shared_ptr<Scene> scene, std::shared_ptr<OGLRenderer> renderer) {
    renderer->render(scene, this->frameBuffer);
    this->renderPassResult = this->frameBuffer->getRenderedResult();
    return this->renderPassResult;
}

