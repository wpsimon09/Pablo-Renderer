//
// Created by wpsimon09 on 06/04/24.
//

#ifndef PABLO_RENDERER_RENDERER_H
#define PABLO_RENDERER_RENDERER_H

#include "Renderer/SceneGraph/Scene.h"
#include "Renderer/Utils/ShaderHelper/ShaderHelper.h"
#include "Renderer/Utils/FrameBuffer/FrameBuffer.h"

enum RENDERER_TYPE{
    COLOR_DEPTH_STENCIL = 1,
    DEPTH_ONLY = 2,
    POST_PROCESSING = 3,
    SINGLE_SHADER = 4
};


class Renderer {
public:
    Renderer() = default;
    RENDERER_TYPE type;

    /***
    * Renders the scene to the provided frame buffer
    * @param frameBuffer frame buffer where to render the scene
    */
    virtual void render(std::shared_ptr<Scene>scene, std::unique_ptr<FrameBuffer>& frameBuffer){};

    virtual void render(std::shared_ptr<Scene>scene, std::unique_ptr<FrameBuffer>& frameBuffer, std::shared_ptr<Shader> shader){};

    virtual void render(std::unique_ptr<FrameBuffer>& frameBuffer){};

    virtual void setInputsForRenderPass(std::vector<std::shared_ptr<TextureBase>> inputs){};
protected:
    std::shared_ptr<Scene> scene;
    GLFWwindow* window;

    /***
    * Renders the scene graph structure in recursive way
    * @param sceneNode scene node to render
    */
    virtual void renderSceneGraph(SceneNode& sceneNode){};

    /***
     * Inputs for the render pass
     */
    std::vector<std::shared_ptr<TextureBase>> renderPassInputs;

};


#endif //PABLO_RENDERER_RENDERER_H
