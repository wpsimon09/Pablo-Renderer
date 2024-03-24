//
// Created by wpsimon09 on 11/01/24.
//

#ifndef PABLO_RENDERER_OGLRENDERER_H
#define PABLO_RENDERER_OGLRENDERER_H

#include "Renderer/SceneGraph/Scene.h"
#include "Renderer/Utils/ShaderHelper/ShaderHelper.h"
#include "Renderer/Utils/FrameBuffer/FrameBuffer.h"

/***
 * Class representing rendered powered by OpenGL api
 */
class OGLRenderer {
public:
    OGLRenderer()=default;

    /***
     * Renders the scene to the provided frame buffer
     * @param frameBuffer frame buffer where to render the scene
     */
    void render(std::shared_ptr<Scene> scene, std::unique_ptr<FrameBuffer>& frameBuffer);
private:
    std::shared_ptr<Scene> scene;
    GLFWwindow* window;

    /***
     * Renders the scene graph structure in recursive way
     * @param sceneNode scene node to render
     */
    void renderSceneGraph(SceneNode& sceneNode);
};

#endif //PABLO_RENDERER_OGLRENDERER_H
