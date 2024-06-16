//
// Created by wpsimon09 on 16/06/24.
//

#include "PixelPicking.h"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"

PixelPicking::PixelPicking() {
    auto texture = std::make_unique<Texture2D>(GLFWHelper::getScreenWidth(), GLFWHelper::getScreenHeight(), GL_RGBA32UI);
    auto pixelPickingShader = ShaderManager::getShader(SHADER_PIXEL_PICKING);
    this->frameBuffer = std::make_unique<FrameBuffer>(GLFWHelper::getScreenWidth(), GLFWHelper::getScreenHeight());
    this->name = "Pixel picking";
    this->rendererType = COLOR_DEPTH_STENCIL;
}

std::shared_ptr<Texture2D> PixelPicking::render(std::shared_ptr<Scene> scene, std::shared_ptr<Renderer> renderer) {
    scene->renderingConstrains = NONE;
    renderer->render(scene,this->frameBuffer);
    this->renderPassResult = this->frameBuffer->getRenderedResult();
    return this->renderPassResult;
}

