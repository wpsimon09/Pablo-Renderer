//
// Created by wpsimon09 on 04/04/24.
//

#ifndef PABLO_RENDERER_DEPTHRENDERER_H
#define PABLO_RENDERER_DEPTHRENDERER_H

#include "Renderer/Renderers/OGLRenderer/OGLRenderer.h"

class DepthRenderer:public OGLRenderer {
public:
    DepthRenderer() = default;

    void render(std::shared_ptr<Scene> scene, std::unique_ptr<FrameBuffer> &frameBuffer) override;

private:
    void renderSceneGraph(SceneNode &sceneNode) override;

};




#endif //PABLO_RENDERER_DEPTHRENDERER_H
