//
// Created by wpsimon09 on 02/02/24.
//

#ifndef PABLO_RENDERER_PABLORENDERER_H
#define PABLO_RENDERER_PABLORENDERER_H
#include "Renderer/SceneGraph/Scene.h"

class PabloRenderer {
public:
    PabloRenderer(Scene* scene, GLFWwindow* window);
    void init();
    void render();
private:



    void renderSceneGraph(SceneNode* sceneNode);

    void processInput(GLFWwindow* window);

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);


};


#endif //PABLO_RENDERER_PABLORENDERER_H
