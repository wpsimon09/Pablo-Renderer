//
// Created by wpsimon09 on 11/01/24.
//

#ifndef PABLO_RENDERER_OGLRENDERER_H
#define PABLO_RENDERER_OGLRENDERER_H

#include "Renderer/Renderers/Renderer.h"
#include "Renderer/Utils/RendererManager/RendererManager.h"
#include "vector"

/***
 * Class representing rendered powered by OpenGL api
 */
class OGLRenderer:public Renderer {
public:
    OGLRenderer():Renderer() { this->type = COLOR_DEPTH_STENCIL; }

    void render(std::shared_ptr<Scene> scene, std::unique_ptr<FrameBuffer>& frameBuffer) override;

    void setInputsForRenderPass(std::vector<std::shared_ptr<TextureBase>> inputs) override;

protected:
    void renderSceneGraph(SceneNode& sceneNode) override;
};

#endif //PABLO_RENDERER_OGLRENDERER_H
