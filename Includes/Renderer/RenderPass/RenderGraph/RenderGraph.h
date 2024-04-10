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

    void preProcessing();

    void render();

    void postProcessing();

    void displayResult(FrameBuffer &frameBuffer);

    std::shared_ptr<Texture2D> getDebugTexture(std::string renderPassResult);
private:
    std::unique_ptr<RendererManager> rendererManager;
    std::map<std::string, std::shared_ptr<Texture2D>> renderResults;

    //hardcoded for now later will be refactored (hopefully)
    std::unique_ptr<ScenePass> scenePass;
    std::unique_ptr<ShadowMapPass> shadowMapPass;

    std::shared_ptr<Scene> scene;
};


#endif //PABLO_RENDERER_RENDERGRAPH_H