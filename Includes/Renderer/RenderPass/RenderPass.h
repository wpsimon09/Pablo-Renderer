//
// Created by wpsimon09 on 24/03/24.
//

#ifndef PABLO_RENDERER_RENDERPASS_H
#define PABLO_RENDERER_RENDERPASS_H
#include "memory"
#include "Renderer/Enums/RenderPassTypes.h"
#include "Renderer/Utils/Texture/Texture2D/Texture2D.h"
#include "Renderer/Utils/FrameBuffer/FrameBuffer.h"
#include "Renderer/Renderers/OGLRenderer/OGLRenderer.h"
#include "Renderer/SceneGraph/Scene.h"
#include "Renderer/Utils/RendererManager/RendererManager.h"

/**
 * @brief Base class for the RenderPasses inherited by concrete render passes
 */
class RenderPass {
public:
    RenderPass();

    /***
     * Method that renders the scene and stores the result inside 2D texture
     * @param scene scene to be rendererd
     * @param renderer renderer to be used such as DEPTH_ONLY or DEPTH_AND_COLOR (see base renderer class)
     * @return rendered scene with appropriate renderer in appropriate texture
     */
    virtual std::shared_ptr<Texture2D> render(std::shared_ptr<Scene> scene, std::shared_ptr<Renderer> renderer) {
        return nullptr;
    }

    /***
     * Renders the post processing effect
     * @param renderedScene renderedScene to the postprocessing effect usualy this is the scene rendered onot the 2d quad
     * @param renderer renderer that will prefome the postprocessing rendering
     * @return rendered result stored in 2D texture
     */
    virtual std::shared_ptr<Texture2D> render(std::shared_ptr<Texture2D> renderedScene,
                                              std::shared_ptr<Renderer> renderer) { return nullptr; }

    /***
     * Return the rendered resutl preformed by the RenderPass
     * @return render pass resutl
     */
    std::shared_ptr<Texture2D> getRenderedResult() { return this->renderPassResult; }

    /***
     * adds input to the render pass
     * @param input vector of inputs that are usualy look up tables
     */
    void addInput(std::shared_ptr<TextureBase> input);

    /***
     * Prepares the render pass for the next frame by clearing frame buffer input and allocated resources
     */
    void prepareForNextFrame();

    /**
     * @brief Renders UI of the concrete render pass (virtual)
     */
    virtual void renderUI();

    /**
     * @brief Retrieves name of the rendre pass
     * @return name of the render pass
     */
    std::string getName() { return this->name; }

    /**
     * @brief Retrieves the frame buffer of the Render Pass
     * @return Frame buffer of the render pass @class FrameBuffer
     */
    FrameBuffer &getFrameBuffer();

    /**
     * @brief Retrieves rendering status of the render pass
     * @return true if render pass is allowed to be rendered false otherwise
     */
    bool canBeRendered() { return this->isActive; }

    /**
     * @brief Retrieves if the render pass is post processing pass
     * @return true if render pass is post processing pass otherwise false
     */
    bool isPostProcess() { return this->isPostProcessingPass; }

    /**
     * @brief Renderer that the render pass is using @see @class Renderer
     */
    RENDERER_TYPE rendererType;

    /**
     * @brief Gets the render pass type such as SCENE_PASS, PIXEL_PICKING_PASS etc..
     * @return render pass type
     */
    RENDER_PASS getRenderPass() { return this->render_pass; }

protected:
    /**
     * @brief Type of the render pass
     */
    RENDER_PASS render_pass;

    /**
     * @brief Name of the render pass
     */
    std::string name;

    /**
     * @brief Determines if the concrete render pass is being rendered
     */
    bool isActive = true;

    /**
     * @brief Determines if the concrete render pass is post processing pass
     */
    bool isPostProcessingPass = false;

    /**
     * @brief Inputs to the render pass
     * @todo Change from textures only to the templated method
     */
    std::vector<std::shared_ptr<TextureBase> > inputs;

    /**
     * @brief Frame buffer where results are being drawn into
     */
    std::unique_ptr<FrameBuffer> frameBuffer;

    /**
     * @brief Texture to store the acctual result
     * can be accessed to preform various operations it holds the colour information
     * @todo set this texture to be colour attachment of the frame buffer by default
     */
    std::shared_ptr<Texture2D> renderPassResult;
};


#endif //PABLO_RENDERER_RENDERPASS_H
