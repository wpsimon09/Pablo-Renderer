//
// Created by wpsimon09 on 11/01/24.
//

#include "OGLRenderer.h"


OGLRenderer::OGLRenderer(Scene *scene) {
    this->scene = scene;
}

void OGLRenderer::render(GLFWwindow *window, GLuint frameBuffer) {

    float currentFrame = static_cast<float>(glfwGetTime());
    this->deltaTime = currentFrame - this->lastFrame;
    this->lastFrame = currentFrame;

    this->scene->setup();

    this->scene->update();

    renderSceneNode(scene->root);
}

void OGLRenderer::renderSceneNode(SceneNode *sceneNode) {
    if (sceneNode->getRenderable()){
        Renderable *renderable = sceneNode->getRenderable();
        Shader *shader = renderable->getShader();

        this->scene->light->update(shader);
        ShaderHelper::setTransfomrationMatrices(shader, sceneNode->getModelMatrix(), this->scene->camera->GetViewMatrix(), this->scene->camera->getProjection());

        sceneNode->render();
    }
    for (std::vector<SceneNode*>::const_iterator i = sceneNode->getChildIteratorStart(); i<sceneNode->getChildIteratorEnd(); ++i) {
        this->renderSceneNode(*i);
    }
}

void OGLRenderer::processInput(GLFWwindow *window) {
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

/*    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        lightPosition.z += lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        lightPosition.z -= lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        lightPosition.x += lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        lightPosition.x -= lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        lightPosition.y -= lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        lightPosition.y += lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        hasNormalMap = 1.0f;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        hasNormalMap = 0.0f;
*/

}

void OGLRenderer::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    this->scene->camera->ProcessMouseScroll(static_cast<float>(yoffset));
}

void OGLRenderer::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xOffset = xpos - lastX;
    float yOffset = ypos - lastY; //calculate how much does mouse move

    lastX = xpos;
    lastY = ypos; //update last mouse position

    this->scene->camera->ProcessMouseMovement(xOffset, yOffset);
}


