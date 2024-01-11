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
        sceneNode->render();

    }
    for (std::vector<SceneNode*>::const_iterator i = sceneNode->getChildIteratorStart(); i<sceneNode->getChildIteratorEnd(); ++i) {
        this->renderSceneNode(*i);
    }
}
