//
// Created by wpsimon09 on 30/03/24.
//

#include "ShadowMapPass.h"


ShadowMapPass::ShadowMapPass() {
    this->frameBuffer = std::make_unique<FrameBuffer>(800, 600);
    this->frameBuffer->makeDepthOnly();
}

std::shared_ptr<Texture2D> ShadowMapPass::render(std::shared_ptr<Scene> scene, std::shared_ptr<OGLRenderer> renderer) {
    scene->renderingConstrains = SHADOW_ONLY;
    //TODO add rendering constrains to the scene as well as call this method in Pablo Renderer with depth renderer and set renderer paramter in the method to be optionsl
    renderer->render(scene, this->frameBuffer);
    this->renderPassResult = frameBuffer->getRenderedResult();
    return this->renderPassResult;
}
