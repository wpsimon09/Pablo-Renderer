//
// Created by wpsimon09 on 15/05/24.
//

#ifndef PABLO_RENDERER_PIXELATION_H
#define PABLO_RENDERER_PIXELATION_H

#include "Renderer/RenderPass/RenderPass.h"

class Pixelation: public RenderPass {
public:
    Pixelation();

    void renderUI() override;

    std::shared_ptr<Texture2D> render(std::shared_ptr<Texture2D> renderedScene, std::shared_ptr<Renderer> renderer) override;
private:
    int pixelSize = 2;
};


#endif //PABLO_RENDERER_PIXELATION_H
