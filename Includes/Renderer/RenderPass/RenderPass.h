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

    /***
     * Method that renders the scene and stores the result inside 2D texture
     * @param scene scene to be rendererd
     * @param renderer renderer to be used such as DEPTH_ONLY or DEPTH_AND_COLOR (see base renderer class)
     * @return rendered scene with appropriate renderer in appropriate texture
     */
    virtual std::shared_ptr<Texture2D> render(std::shared_ptr<Scene> scene, std::shared_ptr<Renderer> renderer){return nullptr;}

    /***
     * Renders the post processing effect
     * @param renderedScene renderedScene to the postprocessing effect usualy this is the scene rendered onot the 2d quad
     * @param renderer renderer that will prefome the postprocessing rendering
     * @return rendered result stored in 2D texture
     */
    virtual std::shared_ptr<Texture2D> render(std::shared_ptr<Texture2D> renderedScene, std::shared_ptr<Renderer> renderer){return nullptr;}

    /***
     * Return the rendered resutl preformed by the RenderPass
     * @return render pass resutl
     */
    std::shared_ptr<Texture2D> getRenderedResult() {return this->renderPassResult;}

    /***
     * adds input to the render pass
     * @param input vector of inputs that are usualy look up tables
     */
    void addInput(std::shared_ptr<TextureBase> input);

    /***
     * Prepares the render pass for the next frame by clearing frame buffer input and allocated resources
     */
    void prepareForNextFrame();

    virtual void renderUI();

    std::string getName() {return this->name;}


    FrameBuffer &getFrameBuffer();


    bool canBeRendered() {return this->isActive;}

    bool isPostProcess() {return this->isPostProcessingPass;}

    RENDERER_TYPE rendererType;
protected:
    std::string name;
    bool isActive = true;

    bool isPostProcessingPass = false;

    std::vector<std::shared_ptr<TextureBase>> inputs;
    std::unique_ptr<FrameBuffer> frameBuffer;
    std::shared_ptr<Texture2D> renderPassResult;
};


#endif //PABLO_RENDERER_RENDERPASS_H
