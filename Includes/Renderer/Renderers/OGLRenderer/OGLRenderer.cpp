//
// Created by wpsimon09 on 11/01/24.
//

#include "OGLRenderer.h"

#include <utility>



void OGLRenderer::render(std::shared_ptr<Scene> scene, std::unique_ptr<FrameBuffer>& frameBuffer) {
    frameBuffer->bind();
    this->scene = std::move(scene);
    glViewport(0,0, frameBuffer->getWidht(), frameBuffer->getHeihgt());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.01f, 0.01f, 0.01f, 1.0f);

    this->scene->update();
    if(Scene::root){
        renderSceneGraph(*Scene::root);
        this->scene->light->render(this->scene->camera->getViewMatrix(), this->scene->camera->getPojectionMatix());
    }else
        std::cerr<<"ROOT NODE OF SCENE GRAPH NOT CREATED";

    this->renderPassInputs.clear();
    this->scene->renderingConstrains = NONE;
}

void OGLRenderer::renderSceneGraph(SceneNode& sceneNode) {
    if (sceneNode.getRenderable() != nullptr){
        int textureSamplerCount = 0;

        // reference ot unique_ptr of renderable inside scene node
        auto& renderable = sceneNode.getRenderable();

        textureSamplerCount = renderable->getObjectMaterial()->getSamplerCount();

        //shared_ptr here
        auto shader = renderable->getShader();

        this->scene->camera->update(shader);

        ShaderHelper::setTransfomrationMatrices(shader, sceneNode.getModelMatrix(), this->scene->camera->getViewMatrix(), this->scene->camera->getPojectionMatix());

        this->scene->light->update(shader, renderable->castsShadwo);

        if(renderable->getObjectMaterial()->supportsIBL){
            scene->getIblPipeLine()->configureShader(shader, textureSamplerCount);
            textureSamplerCount += scene->getIblPipeLine()->getSamplersCount();
        }

        if(!this->renderPassInputs.empty()){
            for(auto& input: this->renderPassInputs){
                input->setSamplerID(textureSamplerCount);
                ShaderHelper::setTextureToShader(shader, *input,input->shaderName);
                textureSamplerCount ++;
            }
        }

        sceneNode.render(this->scene->renderingConstrains);

    }
    for (auto &childNode : sceneNode.getChildren()) {
        this->renderSceneGraph(*childNode);
    }
}

void OGLRenderer::setInputsForRenderPass(std::vector<std::shared_ptr<TextureBase>> inputs) {
    this->renderPassInputs = std::move(inputs);
}



