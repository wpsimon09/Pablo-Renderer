//
// Created by wpsimon09 on 11/01/24.
//

#ifndef PABLO_RENDERER_OGLRENDERER_H
#define PABLO_RENDERER_OGLRENDERER_H

#include "Renderer/SceneGraph/Scene.h"

class OGLRenderer {
public:
    void render(Scene* scene, GLFWwindow* window);
private:
    SceneNode* nodeInProcess;
    void renderSceneNode(SceneNode* sceneNode, glm::mat4 projection, glm::mat4 view);
};


#endif //PABLO_RENDERER_OGLRENDERER_H
