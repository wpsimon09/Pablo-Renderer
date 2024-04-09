//
// Created by wpsimon09 on 09/04/24.
//

#ifndef PABLO_RENDERER_RENDERGRAPH_H
#define PABLO_RENDERER_RENDERGRAPH_H

#include "Renderer/RenderPass/ScenePass/ScenePass.h"
#include "Renderer/RenderPass/ShadowMapPass/ShadowMapPass.h"
#include "map"


class RenderGraph {
public:
    RenderGraph() = default;

    void init();

    void build();

    void render();

    void displayResult();

    std::shared_ptr<TextureBase> getDebugTexture(std::string renderPassResult);
private:
    std::unique_ptr<RendererManager> rendererManager;
    std::map<std::string, std::unique_ptr<RenderPass>> renderPasses;
};


#endif //PABLO_RENDERER_RENDERGRAPH_H
