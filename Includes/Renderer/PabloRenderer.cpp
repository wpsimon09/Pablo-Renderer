//
// Created by wpsimon09 on 02/02/24.
//

#include "PabloRenderer.h"

#include <utility>


void PabloRenderer::init(unsigned int width, unsigned int height) {
    GLFWHelper::setInstance(PabloRenderer::instance);
    if(!GLFWHelper::glInit(width, height))
        std::cerr<<"OPENGL CONTEXT NOT INITIALIZED";
}

void PabloRenderer::render() {

    while (!glfwWindowShouldClose(window)){
        auto currentFrame = static_cast<float>(glfwGetTime());
        this->deltaTime = currentFrame - this->lastFrame;
        this->lastFrame = currentFrame;
        glViewport(0, 0, this->windowWidth, this->windowHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //-----------------
        // INPUT PROCESSING
        //-----------------
        GLFWHelper::processInput(this->window, this->deltaTime);

        //-----------------
        // ACTUAL RENDERING
        //-----------------
        auto currentRenderPass = renderPasses.begin();
        while(currentRenderPass != renderPasses.end()){
            auto responseRenderer = rendererManager->requestRenderer(currentRenderPass->second->rendererType);
            currentRenderPass->second->render(this->scene, responseRenderer);
            currentRenderPass++;
        }

        //----------------------------------
        //DISPLAY THE RESULT OF FRAME BUFFER
        //----------------------------------
        this->outputFrameBuffer->setColorAttachment(renderPasses.find("ScenePass")->second->getRenderedResult());

        this->outputFrameBuffer->dispalyOnScreen();
        debugFrameBuffer->setColorAttachment(renderPasses.find("ShadowMapPass")->second->getRenderedResult());
        debugFrameBuffer->dispalyOnScreen();

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
    glfwTerminate();

}

void PabloRenderer::setWindow(GLFWwindow *window) {
    this->window = window;
    glfwGetWindowSize(this->window, &this->windowWidth, &this->windowHeight);
}

void PabloRenderer::setDebugTexture(std::shared_ptr<TextureBase> debugTexture) {
    this->debugFrameBuffer->changeTexture(*debugTexture);
}

void PabloRenderer::attachScene(std::shared_ptr<Scene> scene) {
    this->scene = std::move(scene);
    this->scene->setup();

    this->outputFrameBuffer = std::make_unique<FrameBuffer>(this->windowWidth, this->windowHeight);

    this->debugFrameBuffer = std::make_unique<FrameBufferDebug>(this->windowWidth, this->windowHeight);

    this->renderPasses.insert({"ScenePass", std::make_unique<ScenePass>()});
    this->renderPasses.insert({"ShadowMapPass", std::make_unique<ShadowMapPass>()});

    this->rendererManager = std::make_unique<RendererManager>();
}

PabloRenderer* PabloRenderer::getInstance() {
    if(PabloRenderer::instance == nullptr){
        PabloRenderer::instance = new PabloRenderer();
        return PabloRenderer::instance;
    }else
        return PabloRenderer::instance;
}

