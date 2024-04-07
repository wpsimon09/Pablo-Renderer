//
// Created by wpsimon09 on 04/04/24.
//

#include "DepthRenderer.h"

void DepthRenderer::render(std::shared_ptr<Scene> scene, std::unique_ptr<FrameBuffer> &frameBuffer) {
    if(frameBuffer->isDepthOnly){
        frameBuffer->bind();
        glViewport(0,0, frameBuffer->getWidht(), frameBuffer->getHeihgt());
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glCheckError();

        this->scene = std::move(scene);
        this->scene->update();

        if(Scene::root){
            renderSceneGraph(*Scene::root);
        }
        else
            throw std::runtime_error("Scene has no root node");
    }
    else{
        throw std::runtime_error("FrameBuffer contains color buffer");
    }
    this->scene->renderingConstrains = NONE;
}

void DepthRenderer::renderSceneGraph(SceneNode &sceneNode) {
    auto& renderalbe = sceneNode.getRenderable();
    if(renderalbe != nullptr){
        this->scene->light->update(shader);
        this->shader->setMat4("model",sceneNode.getModelMatrix());
        sceneNode.render(scene->renderingConstrains, true);
    }
}