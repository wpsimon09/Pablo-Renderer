//
// Created by wpsimon09 on 04/04/24.
//

#ifndef PABLO_RENDERER_DEPTHRENDERER_H
#define PABLO_RENDERER_DEPTHRENDERER_H

#include "Renderer/Renderers/Renderer.h"
#include "memory"

class DepthRenderer:public Renderer {
public:
    DepthRenderer():Renderer(){type = DEPTH_ONLY;};

    void render(std::shared_ptr<Scene> scene, std::unique_ptr<FrameBuffer> &frameBuffer) override;

private:
    void renderSceneGraph(SceneNode &sceneNode) override;
    std::shared_ptr<Shader> shader = std::make_shared<Shader>("VertexShader/ShadowMap/ShadowMapVertex.glsl", "FragmentShader/ShadowMap/ShadowMapFragment.glsl", "DepthMapShader");
};




#endif //PABLO_RENDERER_DEPTHRENDERER_H
