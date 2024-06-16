//
// Created by wpsimon09 on 16/06/24.
//

#ifndef PABLO_RENDERER_SINGLESHADERRENDERER_H
#define PABLO_RENDERER_SINGLESHADERRENDERER_H

#include "Renderer/Renderers/Renderer.h"
#include "Renderer/Utils/RendererManager/RendererManager.h"
#include "vector"

class SingleShaderRenderer:public Renderer {
public:
    SingleShaderRenderer():Renderer() {this->type = SINGLE_SHADER;}

    void render(std::shared_ptr<Scene> scene, std::unique_ptr<FrameBuffer> &frameBuffer, std::shared_ptr<Shader> shader) override;

    void setInputsForRenderPass(std::vector<std::shared_ptr<TextureBase>> inputs) override;

protected:
    std::shared_ptr<Shader> shader;
    void renderSceneGraph(SceneNode &sceneNode) override;
};


#endif //PABLO_RENDERER_SINGLESHADERRENDERER_H
