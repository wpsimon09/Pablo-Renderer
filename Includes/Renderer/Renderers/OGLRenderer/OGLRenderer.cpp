//
// Created by wpsimon09 on 11/01/24.
//

#include "OGLRenderer.h"

#include <utility>



void OGLRenderer::render(std::shared_ptr<Scene> scene, std::unique_ptr<FrameBuffer>& frameBuffer) {
    frameBuffer->bind();
    this->scene = std::move(scene);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.01f, 0.01f, 0.01f, 1.0f);

    this->scene->update();
    if(Scene::root){
        renderSceneGraph(*Scene::root);
        this->scene->light->render(this->scene->camera->GetViewMatrix(), this->scene->camera->getProjection());
    }else
        std::cerr<<"ROOT NODE OF SCENE GRAPH NOT CREATED";
}

void OGLRenderer::renderSceneGraph(SceneNode& sceneNode) {
    if (sceneNode.getRenderable() != nullptr){
        // reference ot unique_ptr of renderable inside scene node
        auto& renderable = sceneNode.getRenderable();

        //shared_ptr here
        auto shader = renderable->getShader();

        this->scene->camera->update(shader);

        ShaderHelper::setTransfomrationMatrices(shader, sceneNode.getModelMatrix(), this->scene->camera->GetViewMatrix(), this->scene->camera->getProjection());

        this->scene->light->update(shader);

        if(shader->supportsIBL){
            scene->getIblPipeLine()->configureShader(shader, renderable->getObjectMaterial()->getSamplerCount());
        }

        sceneNode.render(this->scene->renderingConstrains);

    }
    for (auto &childNode : sceneNode.getChildren()) {
        this->renderSceneGraph(*childNode);
    }
}



