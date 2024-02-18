//
// Created by wpsimon09 on 11/01/24.
//

#include "OGLRenderer.h"


OGLRenderer::OGLRenderer(std::unique_ptr<Scene> scene,  GLFWwindow* window) {
    this->scene = std::move(scene);
    this->window = window;
}

void OGLRenderer::render(FrameBuffer* frameBuffer) {
    frameBuffer->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.11f, 0.11f, 0.11f, 1.0f);

    this->scene->update();

    renderSceneGraph(std::move(Scene::root));
}

void OGLRenderer::renderSceneGraph(std::unique_ptr<SceneNode> sceneNode) {
    if (sceneNode->getRenderable()){
        std::unique_ptr<Renderable> renderable = sceneNode->getRenderable();
        std::unique_ptr<Shader> shader = renderable->getShader();

        this->scene->light->update(std::move(shader));
        this->scene->camera->update(std::move(shader));

        ShaderHelper::setTransfomrationMatrices(std::move(shader), sceneNode->getModelMatrix(), this->scene->camera->GetViewMatrix(), this->scene->camera->getProjection());

        sceneNode->render();
    }
    for (auto &childNode : sceneNode->getChildren()) {
        this->renderSceneGraph(std::move(childNode));
    }
}



