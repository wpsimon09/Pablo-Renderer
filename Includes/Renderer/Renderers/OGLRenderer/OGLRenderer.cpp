//
// Created by wpsimon09 on 11/01/24.
//

#include "OGLRenderer.h"



/*while(!glfwWindowShouldClose(window)){
float currentFrame = static_cast<float>(glfwGetTime());
deltaTime = currentFrame - lastFrame;
lastFrame = currentFrame;
scene->update();
 */

OGLRenderer::OGLRenderer(Scene *scene) {
    this->scene = scene;
    this->camera = scene->getCamera();


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
        shader->use();
        shader->setMat4("projection", this->camera->getProjection());
        shader->setMat4("view", this->camera->GetViewMatrix());
        this->scene->getLight()->update(shader);
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
        camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera->ProcessKeyboard(RIGHT, deltaTime);

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
    this->camera->ProcessMouseScroll(static_cast<float>(yoffset));
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

    this->camera->ProcessMouseMovement(xOffset, yOffset);
}


