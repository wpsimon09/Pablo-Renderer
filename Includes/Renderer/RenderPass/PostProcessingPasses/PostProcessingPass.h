//
// Created by wpsimon09 on 19/05/24.
//

#ifndef PABLO_RENDERER_POSTPROCESSINGPASS_H
#define PABLO_RENDERER_POSTPROCESSINGPASS_H

#include "Renderer/RenderPass/RenderPass.h"

class PostProcessingPass:public RenderPass {
public:
    PostProcessingPass();

    std::shared_ptr<Texture2D> render(std::shared_ptr<Texture2D> renderedScene, std::shared_ptr<Renderer> renderer) override;

    void renderUI() override;

    void addPostProcessingPass(std::unique_ptr<RenderPass> renderPass);

    void prepareForNextFrame();
private:
    std::vector<std::unique_ptr<RenderPass>> postProcessingPasses;
    void mergePasses(std::shared_ptr<Texture2D> passToMerge);

};


#endif //PABLO_RENDERER_POSTPROCESSINGPASS_H
