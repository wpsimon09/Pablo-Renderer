//
// Created by wpsimon09 on 02/02/24.
//

#ifndef PABLO_RENDERER_PABLORENDERER_H
#define PABLO_RENDERER_PABLORENDERER_H
#include "Renderer/SceneGraph/Scene.h"
#include "Renderer/Renderers/OGLRenderer/OGLRenderer.h"
#include "Renderer/Utils/FrameBuffer/FrameBuffer.h"
#include "Renderer/Utils/FrameBuffer/FrameBufferDebug/FrameBufferDebug.h"
#include "Renderer/Utils/Texture/TextureHDR/TextureHDRi.h"

class PabloRenderer {
public:
    PabloRenderer();

    /***
     * Initialize the OpenGL context, widow and pablo render itself
     * @param width width of the window
     * @param height heights of the window
     */
    void init(unsigned int width, unsigned int height);

    /***
     * Attaches scene to the renderer based on what we want to render
     * @param scene scene to be attached
     */
    void attachScene(std::shared_ptr<Scene> scene);

    void render();

    void setDebugTexture(std::shared_ptr<TextureBase> debugTexture);

    ~PabloRenderer(){};
private:
    inline static std::unique_ptr<PabloRenderer> instace;

    std::unique_ptr<OGLRenderer> renderer = nullptr;

    std::shared_ptr<Scene> scene = nullptr;

    GLFWwindow* window = nullptr;

    std::vector<std::unique_ptr<FrameBuffer>> frameBuffers;
    std::unique_ptr<FrameBufferDebug> debugFrameBuffer ;

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

    bool glInit(unsigned int width, unsigned int height);

};


#endif //PABLO_RENDERER_PABLORENDERER_H
