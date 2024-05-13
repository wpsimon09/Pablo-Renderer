//
// Created by wpsimon09 on 12/05/24.
//

#ifndef PABLO_RENDERER_POSTPROCESSINGRENDERER_H
#define PABLO_RENDERER_POSTPROCESSINGRENDERER_H

#include "Renderer/Renderers/Renderer.h"

class PostProcessingRenderer: public Renderer{
public:
    PostProcessingRenderer():Renderer() {this->type = POST_PROCESSING;}

    void setInputsForRenderPass(std::vector<std::shared_ptr<TextureBase>> inputs) override;

    void render(std::unique_ptr<FrameBuffer> &frameBuffer) override;

protected:
    void renderSceneGraph(SceneNode &sceneNode) override;
};


#endif //PABLO_RENDERER_POSTPROCESSINGRENDERER_H
