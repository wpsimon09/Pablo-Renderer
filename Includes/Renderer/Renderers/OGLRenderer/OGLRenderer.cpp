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
void OGLRenderer::render(Scene *scene, GLFWwindow *window) {
    scene->setup();

    renderSceneNode(scene->root, scene->getCamera()->getProjection(), scene->getCamera()->GetViewMatrix());

    scene->update();
}

void OGLRenderer::renderSceneNode(SceneNode *sceneNode,glm::mat4 projection, glm::mat4 view) {
    if (sceneNode->getRenderable()){
        sceneNode->getRenderable()->setProjectionMatrix(projection);
        sceneNode->getRenderable()->setViewMatrix(view);
        sceneNode->render();
    }
    for (std::vector<SceneNode*>::const_iterator i = sceneNode->getChildIteratorStart(); i<sceneNode->getChildIteratorEnd(); ++i) {
        this->renderSceneNode(*i, projection, view);
    }
}
