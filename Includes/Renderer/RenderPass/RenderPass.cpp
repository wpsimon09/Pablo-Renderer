//
// Created by wpsimon09 on 24/03/24.
//

#include "RenderPass.h"

RenderPass::RenderPass() {
    this->renderPassResult = std::make_shared<Texture2D>(GLFWHelper::getScreenWidth(), GLFWHelper::getScreenHeight(), GL_RGBA16F);
}
