//
// Created by wpsimon09 on 11/01/24.
//

#include "OGLRenderer.h"


OGLRenderer::OGLRenderer(Scene *scene,  GLFWwindow* window) {
    this->scene = scene;
    this->window = window;
}

void OGLRenderer::render(GLuint frameBuffer) {

        glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

        this->scene->update();

        renderSceneGraph(Scene::root);

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



