//
// Created by wpsimon09 on 24/03/24.
//

#ifndef PABLO_RENDERER_SCENEPASS_H
#define PABLO_RENDERER_SCENEPASS_H

#include "Renderer/RenderPass/RenderPass.h"

class ScenePass: public RenderPass {


private:
    std::shared_ptr<Texture2D> gPosition;
    std::shared_ptr<Texture2D> gNormal;
    std::shared_ptr<Texture2D> gColourAndShininess;
public:
    void renderUI() override;
    std::vector<std::shared_ptr<TextureBase>> getAdditionalOutputs() override;

    ScenePass();
    std::shared_ptr<Texture2D> render(std::shared_ptr<Scene> scene, std::shared_ptr<Renderer> renderer) override;
};


#endif //PABLO_RENDERER_SCENEPASS_H
