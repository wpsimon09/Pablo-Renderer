//
// Created by wpsimon09 on 11/01/24.
//

#ifndef PABLO_RENDERER_OGLRENDERER_H
#define PABLO_RENDERER_OGLRENDERER_H

#include "Renderer/SceneGraph/Scene.h"
#include "Renderer/Utils/ShaderHelper/ShaderHelper.h"

class OGLRenderer {
public:
    OGLRenderer(Scene* scene, GLFWwindow* window);
    void init();
    void render(GLuint frameBuffer = 0);
private:
    Scene* scene;
    GLFWwindow* window;

    void renderSceneGraph(SceneNode* sceneNode);
};

#endif //PABLO_RENDERER_OGLRENDERER_H
