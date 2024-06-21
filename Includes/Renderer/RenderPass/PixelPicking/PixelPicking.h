//
// Created by wpsimon09 on 16/06/24.
//

#ifndef PABLO_RENDERER_PIXELPICKING_H
#define PABLO_RENDERER_PIXELPICKING_H

#include "Renderer/RenderPass/RenderPass.h"
#include "memory"

class PixelPicking: public RenderPass {

public:
    PixelPicking();

    std::shared_ptr<Texture2D> render(std::shared_ptr<Scene> scene, std::shared_ptr<Renderer> renderer) override;

private:
    std::shared_ptr<Scene> scene;
    std::shared_ptr<Shader> pixelPickingShader;
};


#endif //PABLO_RENDERER_PIXELPICKING_H
