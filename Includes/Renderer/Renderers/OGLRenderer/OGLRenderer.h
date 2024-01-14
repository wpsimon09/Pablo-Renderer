//
// Created by wpsimon09 on 11/01/24.
//

#ifndef PABLO_RENDERER_OGLRENDERER_H
#define PABLO_RENDERER_OGLRENDERER_H

#include "Renderer/SceneGraph/Scene.h"
#include "Renderer/Utils/ShaderHelper/ShaderHelper.h"

class OGLRenderer {
public:
    OGLRenderer(Scene* scene);
    void init();
    void render(GLFWwindow* window, GLuint frameBuffer = 0);
private:
    Scene* scene;

    float deltaTime;
    float lastFrame;
    float lastX = 0;
    float lastY = 0;
    bool firstMouse = true;

    void renderSceneGraph(SceneNode* sceneNode);

    void processInput(GLFWwindow* window);

    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};

#endif //PABLO_RENDERER_OGLRENDERER_H
