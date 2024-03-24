//
// Created by wpsimon09 on 24/03/24.
//

#ifndef PABLO_RENDERER_SCENEPASS_H
#define PABLO_RENDERER_SCENEPASS_H

#include "Renderer/RenderPass/RenderPass.h"

class ScenePass: public RenderPass {
    ScenePass();

public:
    std::shared_ptr<Texture2D> render(std::shared_ptr<Scene> scene, std::shared_ptr<OGLRenderer> renderer) override;
};


#endif //PABLO_RENDERER_SCENEPASS_H
