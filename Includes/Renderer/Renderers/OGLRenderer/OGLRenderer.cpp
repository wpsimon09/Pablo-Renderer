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
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    this->scene->update();
    if(Scene::root){
        renderSceneGraph(*Scene::root);
        this->scene->light->render();
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

        sceneNode.render();

    }
    for (auto &childNode : sceneNode.getChildren()) {
        this->renderSceneGraph(*childNode);
    }
}



