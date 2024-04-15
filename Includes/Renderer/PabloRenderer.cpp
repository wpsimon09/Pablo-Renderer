//
// Created by wpsimon09 on 02/02/24.
//

#include "PabloRenderer.h"

#include <utility>


void PabloRenderer::init(unsigned int width, unsigned int height) {
    GLFWHelper::setInstance(PabloRenderer::instance);
    if(!GLFWHelper::glInit(width, height))
        std::cerr<<"OPENGL CONTEXT NOT INITIALIZED";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    this->imGuiIo = &ImGui::GetIO();
    (void)imGuiIo;
    imGuiIo->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    imGuiIo->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui::StyleColorsDark();
    const char* glsl_version = "#version 130";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void PabloRenderer::render() {
    bool shadow_demo_window = true;

    while (!glfwWindowShouldClose(window)){
        auto currentFrame = static_cast<float>(glfwGetTime());
        this->deltaTime = currentFrame - this->lastFrame;
        this->lastFrame = currentFrame;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow(&shadow_demo_window);

        //-----------------
        // INPUT PROCESSING
        //-----------------
        GLFWHelper::processInput(this->window, this->deltaTime);

        //-----------------
        // ACTUAL RENDERING
        //-----------------
        this->renderGraph->preProcessing();

        this->renderGraph->render();

        this->renderGraph->postProcessing();

        this->renderGraph->displayResult( *this->outputFrameBuffer);

        //----------------------------------
        //DISPLAY THE RESULT OF FRAME BUFFER
        //----------------------------------
        debugFrameBuffer->setColorAttachment(renderGraph->getDebugTexture("ShadowMapPass"));
        debugFrameBuffer->dispalyOnScreen();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        this->renderGraph->prepareForNextFrame();
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

    this->renderGraph = std::make_unique<RenderGraph>(this->scene);
    this->renderGraph->init();

    this->outputFrameBuffer = std::make_unique<FrameBuffer>(GLFWHelper::getScreenWidth(), GLFWHelper::getScreenHeight());

    this->debugFrameBuffer = std::make_unique<FrameBufferDebug>(this->windowWidth, this->windowHeight);
}

PabloRenderer* PabloRenderer::getInstance() {
    if(PabloRenderer::instance == nullptr){
        PabloRenderer::instance = new PabloRenderer();
        return PabloRenderer::instance;
    }else
        return PabloRenderer::instance;
}

