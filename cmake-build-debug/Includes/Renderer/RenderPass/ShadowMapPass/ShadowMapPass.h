//
// Created by wpsimon09 on 30/03/24.
//

#ifndef PABLO_RENDERER_SHADOWMAPPASS_H
#define PABLO_RENDERER_SHADOWMAPPASS_H

#include "Renderer/RenderPass/RenderPass.h"

class ShadowMapPass:public RenderPass {
public:
    ShadowMapPass();

    std::shared_ptr<Texture2D> render(std::shared_ptr<Scene> scene, std::shared_ptr<Renderer> renderer) override;
};


#endif //PABLO_RENDERER_SHADOWMAPPASS_H
