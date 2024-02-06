//
// Created by wpsimon09 on 02/02/24.
//

#ifndef PABLO_RENDERER_PABLORENDERER_H
#define PABLO_RENDERER_PABLORENDERER_H
#include "Renderer/SceneGraph/Scene.h"
#include "Renderer/Renderers/OGLRenderer/OGLRenderer.h"
#include "Renderer/Utils/FrameBuffer/FrameBuffer.h"
#include "Renderer/Utils/FrameBuffer/FrameBufferDebug/FrameBufferDebug.h"
class PabloRenderer {
public:
    PabloRenderer(Scene* scene, GLFWwindow* window);

    void init();
    void render();
private:
    inline static PabloRenderer *instace ;

    OGLRenderer *renderer;

    Scene* scene;

    GLFWwindow* window;

    std::vector<FrameBuffer*> frameBuffers;

    float deltaTime;
    float lastFrame;
    float lastX = 0;
    float lastY = 0;
    bool firstMouse = true;
    float lightSpeed;

    int windowHeight;
    int windowWidth;

    void setWindow(GLFWwindow* window);

    void processInput(GLFWwindow* window);

    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

};


#endif //PABLO_RENDERER_PABLORENDERER_H
