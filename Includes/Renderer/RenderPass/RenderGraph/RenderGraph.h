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
    explicit RenderGraph(std::shared_ptr<Scene> scene);

    void init();

    void build();

    void render();

    void displayResult(FrameBuffer &frameBuffer);

    std::shared_ptr<Texture2D> getDebugTexture(std::string renderPassResult);
private:
    std::unique_ptr<RendererManager> rendererManager;
    std::map<std::string, std::unique_ptr<RenderPass>> renderPasses;
    std::shared_ptr<Scene> scene;
};


#endif //PABLO_RENDERER_RENDERGRAPH_H
