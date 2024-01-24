//
// Created by wpsimon09 on 11/01/24.
//

#include "OGLRenderer.h"


OGLRenderer::OGLRenderer(Scene *scene,  GLFWwindow* window) {
    this->scene = scene;
    OGLRenderer::instace = this;
    this->lightSpeed = 2.5f * deltaTime;
    this->window = window;
    glfwGetWindowSize(window, &this->windowWidth, &this->windowHeight);

    glfwSetCursorPosCallback(window, OGLRenderer::mouse_callback);
    glfwSetScrollCallback(window, OGLRenderer::scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

void OGLRenderer::render(GLuint frameBuffer) {
    while (!glfwWindowShouldClose(window)) {

        glViewport(0, 0, this->windowWidth, this->windowHeight);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.01f, 0.01f, 0.01f, 1.0f);


        float currentFrame = static_cast<float>(glfwGetTime());
        this->deltaTime = currentFrame - this->lastFrame;
        this->lastFrame = currentFrame;

        this->processInput(this->window);

        this->scene->setup();

        this->scene->update();

        renderSceneGraph(Scene::root);

        glfwSwapBuffers(this->window);
        glfwPollEvents();
    }

    glfwTerminate();
}

void OGLRenderer::renderSceneGraph(SceneNode *sceneNode) {
    if (sceneNode->getRenderable()){
        Renderable *renderable = sceneNode->getRenderable();
        Shader *shader = renderable->getShader();

        this->scene->light->update(shader);
        this->scene->camera->update(shader);

        ShaderHelper::setTransfomrationMatrices(shader, sceneNode->getModelMatrix(), this->scene->camera->GetViewMatrix(), this->scene->camera->getProjection());

        sceneNode->render();
    }
    for (std::vector<SceneNode*>::const_iterator i = sceneNode->getChildIteratorStart(); i<sceneNode->getChildIteratorEnd(); ++i) {
        this->renderSceneGraph(*i);
    }
}

void OGLRenderer::processInput(GLFWwindow *window) {
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

void OGLRenderer::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    instace->scene->camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void OGLRenderer::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
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


