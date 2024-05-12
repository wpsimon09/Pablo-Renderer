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

        auto lights = this->scene->lights.begin();
        while(lights!= this->scene->lights.end()){
            lights->second->render(this->scene->camera->getViewMatrix(), this->scene->camera->getPojectionMatix());
            lights++;
        }

    }else
        std::cerr<<"ROOT NODE OF SCENE GRAPH NOT CREATED";

    this->renderPassInputs.clear();
    this->scene->renderingConstrains = NONE;
}

void OGLRenderer::renderSceneGraph(SceneNode& sceneNode) {
    if (sceneNode.getRenderable() != nullptr){
        //glCullFace(GL_BACK);
        int textureSamplerCount = 0;

        // reference ot unique_ptr of renderable inside scene node
        auto& renderable = sceneNode.getRenderable();

        if(renderable->getBackFaceCull()){
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
        }

        textureSamplerCount = renderable->getObjectMaterial()->getSamplerCount();

        //shared_ptr here
        auto shader = renderable->getShader();

        this->scene->camera->update(shader);

        ShaderHelper::setTransfomrationMatrices(shader, sceneNode.getModelMatrix(), this->scene->camera->getViewMatrix(), this->scene->camera->getPojectionMatix());

        // update the renderable that contains light and lights themselfs

        if(shader->supportsIBL){
            scene->getIblPipeLine()->configureShader(shader, textureSamplerCount);
            textureSamplerCount += scene->getIblPipeLine()->getSamplersCount()+1;
        }

        if(shader->supportsAreaLight){
            textureSamplerCount ++;
            this->scene->lights.find(AREA)->second->setCurrentSampler(textureSamplerCount);
            textureSamplerCount = textureSamplerCount + 3;
        }

        auto lights = this->scene->lights.begin();
        while (lights != this->scene->lights.end()){
            lights->second->update(shader, renderable->castsShadwo);
            lights++;
        }


        if(!this->renderPassInputs.empty()){
            for(auto& input: this->renderPassInputs){
                textureSamplerCount ++;
                input->setSamplerID(textureSamplerCount);
                ShaderHelper::setTextureToShader(shader, *input, input->shaderName);
            }
        }

        sceneNode.render(this->scene->renderingConstrains);

    }
    for (auto &childNode : sceneNode.getChildren()) {
        this->renderSceneGraph(*childNode);
    }
    glDisable(GL_CULL_FACE);
}

void OGLRenderer::setInputsForRenderPass(std::vector<std::shared_ptr<TextureBase>> inputs) {
    this->renderPassInputs = std::move(inputs);
}



