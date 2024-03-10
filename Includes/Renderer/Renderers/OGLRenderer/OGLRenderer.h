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
    /***
     * Creates an instance of the OGLRenderer class
     * @param scene
     * @param window
     */
    OGLRenderer(std::shared_ptr<Scene> scene, GLFWwindow* window);
    void init();

    /***
     * Renders the scene to the provided frame buffer
     * @param frameBuffer frame buffer where to render the scene
     */
    void render(std::unique_ptr<FrameBuffer>& frameBuffer);
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
