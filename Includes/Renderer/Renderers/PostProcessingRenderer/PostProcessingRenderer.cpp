//
// Created by wpsimon09 on 12/05/24.
//

#include "PostProcessingRenderer.h"

#include "Renderer/PabloRenderer.h"

void PostProcessingRenderer::setInputsForRenderPass(std::vector<std::shared_ptr<TextureBase>> inputs) {
    this->renderPassInputs = std::move(inputs);
}

void PostProcessingRenderer::renderSceneGraph(SceneNode &sceneNode) {
    //Renderer::renderSceneGraph(sceneNode);
}

void PostProcessingRenderer::render(std::unique_ptr<FrameBuffer> &frameBuffer) {
    frameBuffer->bind();
    glViewport(0,0, frameBuffer->getWidht(), frameBuffer->getHeihgt());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.01f, 0.01f, 0.01f, 1.0f);

    auto shader = frameBuffer->getShader();
    shader->use();

    shader->setMat4("Projection", scene->camera->getPojectionMatix());
    shader->setMat4("invProjection", glm::inverse(scene->camera->getPojectionMatix()));

    shader->setMat4("View", scene->camera->getViewMatrix());
    shader->setMat4("invView", glm::inverse(scene->camera->getViewMatrix()));

    int textureCount = 0;
    for(auto &input: this->renderPassInputs){
        input->setSamplerID(textureCount);
        ShaderHelper::setTextureToShader(shader, *input, input->shaderName);
        textureCount++;
    }
    frameBuffer->renderGeomtry();
}
