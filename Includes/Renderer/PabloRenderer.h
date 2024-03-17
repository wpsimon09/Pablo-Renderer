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

    /***
     * Gets the instance of the Pablo Renderer by usage of raw pointers
     * @return pointer to static instance of PabloRenderer class
     */
    static PabloRenderer* getInstance();

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

    /***
     * Renders the attached scene
     */
    void render();

    /***
     * Sets the texture to the small rectangle on top right corner
     * @param debugTexture
     */
    void setDebugTexture(std::shared_ptr<TextureBase> debugTexture);

    ~PabloRenderer(){delete PabloRenderer::instance;};
private:
    PabloRenderer();

    inline static PabloRenderer* instance = nullptr;

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

    /***
     * Sets the window where to draw to
     * @param window window where to draw
     */
    void setWindow(GLFWwindow* window);

    /***
     * Process the input for the application
     * @param window window in which to process the input
     */
    void processInput(GLFWwindow* window);


    /***
     * Processes event when mouse wheel has scrolled
     * @param window window in which to event occurred
     * @param xoffset offset on x axis
     * @param yoffset offset on y axis
     */
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

    /***
     * Function that process mouse movement call back
     * @param window window in which to process the callback
     * @param xpos position on x axis
     * @param ypos position on y axis
     */
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

    /***
     * Initializes OpenGL context
     * @param width width of the window
     * @param height height of the height
     * @return true if the context was initialized otherwise false
     */
    bool glInit(unsigned int width, unsigned int height);

};


#endif //PABLO_RENDERER_PABLORENDERER_H
