//
// Created by wpsimon09 on 02/02/24.

#ifndef PABLO_RENDERER_PABLORENDERER_H
#define PABLO_RENDERER_PABLORENDERER_H


#include "map"
#include <iterator>
#include "Renderer/SceneGraph/Scene.h"
#include "Renderer/Renderers/OGLRenderer/OGLRenderer.h"
#include "Renderer/Utils/FrameBuffer/FrameBuffer.h"
#include "Renderer/Utils/FrameBuffer/FrameBufferDebug/FrameBufferDebug.h"
#include "Renderer/Utils/Texture/TextureHDR/TextureHDRi.h"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"
#include "Renderer/RenderPass/RenderPass.h"
#include "Renderer/RenderPass/ScenePass/ScenePass.h"
#include "Renderer/RenderPass/ShadowMapPass/ShadowMapPass.h"
#include "Renderer/RenderPass/RenderGraph/RenderGraph.h"
#include "Renderer/UI/UI.h"



/**
 * This is a god class that starts up everything
 * [1] In the beginning God created the heaven and the earth.
 * [2] And the earth was without form, and void; and darkness was upon the face of the deep.
 * And the Spirit of God moved upon the face of the waters.
 * [3] And God said, Let there be light: and there was light.
 */
class PabloRenderer {
public:

    /***
     * Gets the instance of the Pablo Renderer by usage of raw pointers
     * @return pointer to static instance of PabloRenderer class
     * @desingPattern Singleton
     */
    static PabloRenderer* getInstance();

    /***
     * Initialize the OpenGL context, widow and pablo render itself
     * @param width width of the window
     * @param height heights of the window
     */
    void init(unsigned int width = 0, unsigned int height=0);

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

    std::shared_ptr<Scene> getScene(){return this->scene;}

    RenderGraph &getRenderGraph() {return *this->renderGraph;}

    GLFWwindow * getWindow() {return this->window;}

    /***
     * Sets the window where to draw to
    * @param window window where to draw
    */
    void setWindow(GLFWwindow* window);

    ~PabloRenderer(){delete PabloRenderer::instance;}
private:
    PabloRenderer() = default;

    inline static PabloRenderer* instance = nullptr;

    std::shared_ptr<Scene> scene = nullptr;

    GLFWwindow* window = nullptr;

    std::unique_ptr<FrameBuffer> outputFrameBuffer;
    std::unique_ptr<FrameBufferDebug> debugFrameBuffer ;
    std::unique_ptr<RenderGraph> renderGraph;

public:
    float deltaTime;
    float lastFrame;
    float lastX = 0;
    float lastY = 0;
    bool firstMouse = true;
    float lightSpeed;

    int windowHeight;
    int windowWidth;

    ImGuiIO *imGuiIo;
};


#endif //PABLO_RENDERER_PABLORENDERER_H
