//
// Created by wpsimon09 on 16/06/24.
//

#include "PixelPicking.h"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"

PixelPicking::PixelPicking(){

    auto texture = std::make_unique<Texture2D>(800, 600, GL_RGBA32F);
    this->frameBuffer = std::make_unique<FrameBuffer>(1920, 1080,nullptr, std::move(texture));
    this->name = "Pixel picking";
    this->rendererType = SINGLE_SHADER;
    this->render_pass  = PIXEL_PICKING_PASS;
    this->pixelPickingShader = ShaderManager::getShader(SHADER_PIXEL_PICKING);
}

std::shared_ptr<Texture2D> PixelPicking::render(std::shared_ptr<Scene> scene, std::shared_ptr<Renderer> renderer) {
    scene->renderingConstrains = NONE;
    renderer->render(scene,this->frameBuffer, this->pixelPickingShader);
    this->renderPassResult = this->frameBuffer->getRenderedResult();
    return this->renderPassResult;
}

