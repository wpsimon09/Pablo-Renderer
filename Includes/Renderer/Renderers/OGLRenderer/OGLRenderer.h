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
    void setWindow(GLFWwindow* window);
private:
    inline static OGLRenderer *instace ;

    Scene* scene;

    GLFWwindow* window;

    float deltaTime;
    float lastFrame;
    float lastX = 0;
    float lastY = 0;
    bool firstMouse = true;
    float lightSpeed ;

    int windowHeight;
    int windowWidth;

    void renderSceneGraph(SceneNode* sceneNode);

    void processInput(GLFWwindow* window);

   static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

   static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};

#endif //PABLO_RENDERER_OGLRENDERER_H
