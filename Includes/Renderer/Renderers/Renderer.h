//
// Created by wpsimon09 on 06/04/24.
//

#ifndef PABLO_RENDERER_RENDERER_H
#define PABLO_RENDERER_RENDERER_H

#include "Renderer/SceneGraph/Scene.h"
#include "Renderer/Utils/ShaderHelper/ShaderHelper.h"
#include "Renderer/Utils/FrameBuffer/FrameBuffer.h"

enum RENDERER_TYPE {
    COLOR_DEPTH_STENCIL = 1,
    DEPTH_ONLY = 2,
    POST_PROCESSING = 3,
    SINGLE_SHADER = 4
};

/**
 * @brief Class that holds virtual methods to be implemented by the concrete renders
 */
class Renderer {
public:
    Renderer() = default;

    RENDERER_TYPE type;

    /***
    * Renders the scene to the provided frame buffer (virtual)
    * @param frameBuffer frame buffer where to render the scene
    */
    virtual void render(std::shared_ptr<Scene> scene, std::unique_ptr<FrameBuffer> &frameBuffer) {
    };

    /**
     * @brief Renders using specified paramaeters (virtual)
     * @param scene scene to be rendered @see @class Scene
     * @param frameBuffer frame buffer into which to render the scene, ideally it should contain at least colour buffer
     * @param shader shader to be utilizied throught the render pass, meaning all rendered geometry will have the same material, mainly used for pixel picking
     * @see @class PixelPicking
     */
    virtual void render(std::shared_ptr<Scene> scene, std::unique_ptr<FrameBuffer> &frameBuffer,
                        std::shared_ptr<Shader> shader) {
    };

    /**
     * @brief Renders whatever is specified by the parameters (virtual)
     * @param frameBuffer frame buffer into which to render the scene
     * @note this method is mainly used for the post processing steps
     */
    virtual void render(std::unique_ptr<FrameBuffer> &frameBuffer) {
    };

    /**
     * @brief Sets the inputs in form of texture to the frame buffer
     * @param inputs Textures to be used during the render pass
     * @todo Make it templated instead of the texture
     */
    virtual void setInputsForRenderPass(std::vector<std::shared_ptr<TextureBase> > inputs) {
    };

    void setScene(std::shared_ptr<Scene> scene){this->scene = scene;}

protected:
    /**
     * @brief Scene to render
     */
    std::shared_ptr<Scene> scene;

    /**
     * @brief Window with OpenGL context initi
     */
    GLFWwindow *window;

    /***
    * Renders the scene graph structure in recursive way
    * @param sceneNode scene node to render
    */
    virtual void renderSceneGraph(SceneNode &sceneNode) {
    };

    /***
     * Inputs for the render pass
     * @todo remake to be templated
     */
    std::vector<std::shared_ptr<TextureBase> > renderPassInputs;
};


#endif //PABLO_RENDERER_RENDERER_H
