//
// Created by wpsimon09 on 16/06/24.
//

#include "SingleShaderRenderer.h"

void SingleShaderRenderer::render(std::shared_ptr<Scene> scene, std::unique_ptr<FrameBuffer> &frameBuffer, std::shared_ptr<Shader> shader) {
    frameBuffer->bind();
    this->scene = scene;
    this->shader = shader;
    glViewport(0,0, frameBuffer->getWidht(), frameBuffer->getHeihgt());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.01f, 0.01f, 0.01f, 1.0f);

    this->scene->update();
    if(Scene::root){
        renderSceneGraph(*Scene::root);
    }else
        std::cerr<<"ROOT NODE OF SCENE GRAPH NOT CREATED";

    this->renderPassInputs.clear();
    this->scene->renderingConstrains = NONE;
}

void SingleShaderRenderer::renderSceneGraph(SceneNode &sceneNode) {
    if(sceneNode.getRenderable() != nullptr){
        ShaderHelper::setTransfomrationMatrices(shader, sceneNode.getModelMatrix(), this->scene->camera->getViewMatrix(), this->scene->camera->getPojectionMatix());

        shader->setInt("")

    }

    for (auto &childNode : sceneNode.getChildren()) {
        this->renderSceneGraph(*childNode);
    }
}


void SingleShaderRenderer::setInputsForRenderPass(std::vector<std::shared_ptr<TextureBase>> inputs) {
    this->renderPassInputs = std::move(inputs);
}

