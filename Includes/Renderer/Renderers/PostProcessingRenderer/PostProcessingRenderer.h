//
// Created by wpsimon09 on 12/05/24.
//

#ifndef PABLO_RENDERER_POSTPROCESSINGRENDERER_H
#define PABLO_RENDERER_POSTPROCESSINGRENDERER_H

#include "Renderer/Renderers/Renderer.h"

class PostProcessingRenderer: public Renderer{
public:
    PostProcessingRenderer():Renderer() {this->type = POST_PROCESSING;}

    void render(std::shared_ptr<Scene> scene, std::unique_ptr<FrameBuffer> &frameBuffer) override;

    void setInputsForRenderPass(std::vector<std::shared_ptr<TextureBase>> inputs) override;

protected:
    void renderSceneGraph(SceneNode &sceneNode) override;
};


#endif //PABLO_RENDERER_POSTPROCESSINGRENDERER_H
