//
// Created by wpsimon09 on 11/01/24.
//

#include "OGLRenderer.h"


OGLRenderer::OGLRenderer(std::shared_ptr<Scene> scene,  GLFWwindow* window) {
    this->scene = std::move(scene);
    this->window = window;
}

void OGLRenderer::render(std::unique_ptr<FrameBuffer>& frameBuffer) {
    frameBuffer->bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.11f, 0.11f, 0.11f, 1.0f);

    this->scene->update();
    if(Scene::root){
        renderSceneGraph(*Scene::root);
    }else
        std::cerr<<"ROOT NODE OF SCENE GRAPH NOT CREATED";
}

void OGLRenderer::renderSceneGraph(SceneNode& sceneNode) {
    if (sceneNode.getRenderable()){
        // reference ot unique_ptr of renderable inside scene node
        auto& renderable = sceneNode.getRenderable();

        //shared_ptr here
        auto shader = renderable->getShader();

        this->scene->light->update(std::move(shader));
        this->scene->camera->update(std::move(shader));

        ShaderHelper::setTransfomrationMatrices(std::move(shader), sceneNode.getModelMatrix(), this->scene->camera->GetViewMatrix(), this->scene->camera->getProjection());

        sceneNode.render();
    }
    for (auto &childNode : sceneNode.getChildren()) {
        this->renderSceneGraph(*childNode);
    }
}



