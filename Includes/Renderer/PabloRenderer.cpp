//
// Created by wpsimon09 on 02/02/24.
//

#include "PabloRenderer.h"

PabloRenderer::PabloRenderer(Scene *scene, GLFWwindow *window) {
    this->scene = scene;
    PabloRenderer::instace = this;
    this->lightSpeed = 2.5f * deltaTime;
    this->window = window;
    this->renderer = new OGLRenderer(scene, window);

    glfwGetWindowSize(window, &this->windowWidth, &this->windowHeight);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    this->frameBuffers.push_back(new FrameBuffer(this->windowWidth, this->windowHeight));
    this->frameBuffers.push_back(new FrameBufferDebug(this->windowWidth, this->windowHeight));
}

void PabloRenderer::init() {
}

void PabloRenderer::render() {
    while (!glfwWindowShouldClose(window)){
        float currentFrame = static_cast<float>(glfwGetTime());
        this->deltaTime = currentFrame - this->lastFrame;
        this->lastFrame = currentFrame;

        glViewport(0, 0, this->windowWidth, this->windowHeight);

        //-----------------
        // INPUT PROCESSING
        //-----------------
        this->processInput(this->window);

        //-----------------
        // ACTUAL RENDERING
        //-----------------
        this->renderer->render(this->frameBuffers[0]);
        this->renderer->render(this->frameBuffers[1]);

        //----------------------------------
        //DISPLAY THE RESULT TO FRAME BUFFER
        //----------------------------------
        for(auto &frameBuffer: this->frameBuffers){
            frameBuffer->dispalyOnScreen();
        }

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
