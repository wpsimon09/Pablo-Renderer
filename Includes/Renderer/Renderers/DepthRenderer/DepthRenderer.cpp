//
// Created by wpsimon09 on 04/04/24.
//

#include "DepthRenderer.h"

void DepthRenderer::render(std::shared_ptr<Scene> scene, std::unique_ptr<FrameBuffer> &frameBuffer) {
    if(frameBuffer->isDepthOnly){
        frameBuffer->bind();
        glClear(GL_DEPTH_BUFFER_BIT);
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
}

void DepthRenderer::renderSceneGraph(SceneNode &sceneNode) {
    auto& renderalbe = sceneNode.getRenderable();
    if(renderalbe != nullptr){
        this->scene->light->update(shader);
        this->shader->setMat4("model",sceneNode.getModelMatrix());
        sceneNode.render(GEOMETRY_ONLY);
    }
}