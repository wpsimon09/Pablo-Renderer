//
// Created by wpsimon09 on 11/01/24.
//

#ifndef PABLO_RENDERER_OGLRENDERER_H
#define PABLO_RENDERER_OGLRENDERER_H

#include "Renderer/SceneGraph/Scene.h"

class OGLRenderer {
public:
    OGLRenderer(Scene* scene);
    void render(GLFWwindow* window, GLuint frameBuffer = 0);
private:
    Camera* camera;
    Scene* scene;
    SceneNode* nodeInProcess;
    void renderSceneNode(SceneNode* sceneNode);

};


#endif //PABLO_RENDERER_OGLRENDERER_H
