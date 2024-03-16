//
// Created by wpsimon09 on 02/02/24.
//

#include "PabloRenderer.h"

PabloRenderer::PabloRenderer() {
    this->lightSpeed = 2.5f * deltaTime;
    PabloRenderer::instace.reset(this);
}

void PabloRenderer::init(unsigned int width, unsigned int height) {

    this->glInit(width, height);

    glfwGetWindowSize(window, &this->windowWidth, &this->windowHeight);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    this->frameBuffers.push_back(std::make_unique<FrameBuffer>(this->windowWidth, this->windowHeight));

    this->debugFrameBuffer = std::make_unique<FrameBufferDebug>(this->windowWidth, this->windowHeight);
}

void PabloRenderer::render() {

    while (!glfwWindowShouldClose(window)){
        float currentFrame = static_cast<float>(glfwGetTime());
        this->deltaTime = currentFrame - this->lastFrame;
        this->lastFrame = currentFrame;
        glViewport(0, 0, this->windowWidth, this->windowHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //-----------------
        // INPUT PROCESSING
        //-----------------
        this->processInput(this->window);

        //-----------------
        // ACTUAL RENDERING
        //-----------------
        this->renderer->render(this->frameBuffers[0]);

        //----------------------------------
        //DISPLAY THE RESULT OF FRAME BUFFER
        //----------------------------------
        for(auto &frameBuffer: this->frameBuffers){
            frameBuffer->dispalyOnScreen();
        }
        //debugFrameBuffer->dispalyOnScreen();

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }
    glfwTerminate();

}

void PabloRenderer::setWindow(GLFWwindow *window) {
    this->window = window;
    glfwGetWindowSize(this->window, &this->windowWidth, &this->windowHeight);
}


void PabloRenderer::processInput(GLFWwindow *window) {
    this->scene->light->processInput(window);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    const float lightSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        this->scene->camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        this->scene->camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        this->scene->camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        this->scene->camera->ProcessKeyboard(RIGHT, deltaTime);
}

void PabloRenderer::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    instace->scene->camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void PabloRenderer::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (instace->firstMouse) // initially set to true
    {
        instace->lastX = xpos;
        instace->lastY = ypos;
        instace->firstMouse = false;
    }

    float xOffset = xpos - instace->lastX;
    float yOffset = ypos - instace->lastY; //calculate how much does mouse move

    instace->lastX = xpos;
    instace->lastY = ypos; //update last mouse position

    instace->scene->camera->ProcessMouseMovement(xOffset, yOffset);

}

void PabloRenderer::setDebugTexture(std::shared_ptr<TextureBase> debugTexture) {
    this->debugFrameBuffer->changeTexture(*debugTexture);
}

void PabloRenderer::attachScene(std::shared_ptr<Scene> scene) {
    this->scene = scene;
    this->scene->setup();

    this->renderer = std::make_unique<OGLRenderer>(std::move(scene), this->window);
}

bool PabloRenderer::glInit(unsigned int width, unsigned int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_SAMPLES, 8);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    this->window = glfwCreateWindow(width, height, "Pablo-renderer", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    //this code is to make context on the window current and to initialize glad
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_FRAMEBUFFER_SRGB);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    return true;
}
