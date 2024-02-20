//
// Created by wpsimon09 on 11/01/24.
//

#include "OGLRenderer.h"


OGLRenderer::OGLRenderer(std::shared_ptr<Scene> scene,  GLFWwindow* window) {
    this->scene = std::move(scene);
    this->window = window;
}

void OGLRenderer::render(std::shared_ptr<FrameBuffer> frameBuffer) {
    frameBuffer->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.11f, 0.11f, 0.11f, 1.0f);

    this->scene->update();

    renderSceneGraph(std::move(Scene::root));
}

void OGLRenderer::renderSceneGraph(std::shared_ptr<SceneNode> sceneNode) {
    if (sceneNode->getRenderable()){
        auto renderable = sceneNode->getRenderable();
        auto shader = renderable->getShader();

        this->scene->light->update(std::move(shader));
        this->scene->camera->update(std::move(shader));

        ShaderHelper::setTransfomrationMatrices(std::move(shader), sceneNode->getModelMatrix(), this->scene->camera->GetViewMatrix(), this->scene->camera->getProjection());

        sceneNode->render();
    }
    for (auto &childNode : sceneNode->getChildren()) {
        this->renderSceneGraph(std::move(childNode));
    }
}



