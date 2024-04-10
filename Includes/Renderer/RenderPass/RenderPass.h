//
// Created by wpsimon09 on 24/03/24.
//

#ifndef PABLO_RENDERER_RENDERPASS_H
#define PABLO_RENDERER_RENDERPASS_H
#include "memory"
#include "Renderer/Utils/Texture/Texture2D/Texture2D.h"
#include "Renderer/Utils/FrameBuffer/FrameBuffer.h"
#include "Renderer/Renderers/OGLRenderer/OGLRenderer.h"
#include "Renderer/SceneGraph/Scene.h"
#include "Renderer/Utils/RendererManager/RendererManager.h"


class RenderPass {
public:
    RenderPass();

    virtual std::shared_ptr<Texture2D> render(std::shared_ptr<Scene> scene, std::shared_ptr<Renderer> renderer){return nullptr;}

    virtual std::shared_ptr<Texture2D> render(std::shared_ptr<Texture2D> input, std::shared_ptr<OGLRenderer> renderer){return nullptr;}

    std::shared_ptr<Texture2D> getRenderedResult() {return this->renderPassResult;}

    void addInput(std::shared_ptr<TextureBase> input);

    void prepareForNextFrame();

    RENDERER_TYPE rendererType;
protected:
    std::vector<std::shared_ptr<TextureBase>> inputs;
    std::unique_ptr<FrameBuffer> frameBuffer;
    std::shared_ptr<Texture2D> renderPassResult;
};


#endif //PABLO_RENDERER_RENDERPASS_H
