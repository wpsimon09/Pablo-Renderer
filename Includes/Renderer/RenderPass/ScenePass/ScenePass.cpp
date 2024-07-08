//
// Created by wpsimon09 on 24/03/24.
//

#include "ScenePass.h"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"


ScenePass::ScenePass():RenderPass() {
    glm::vec2 screenDimentions = GLFWHelper::getScreenDimensions();

    this->gNormal = std::make_shared<Texture2D>(screenDimentions.x, screenDimentions.y, GL_RGBA16F);
    gNormal->generateMipMaps();
    gNormal->shaderName = "gNormal";

    this->gPosition = std::make_shared<Texture2D>(screenDimentions.x, screenDimentions.y, GL_RGB16F);
    gPosition->generateMipMaps();
    gPosition->shaderName = "gPosition";

    this->gColourAndShininess = std::make_shared<Texture2D>(screenDimentions.x, screenDimentions.y, GL_RGBA16F);
    gColourAndShininess->generateMipMaps();
    gColourAndShininess->shaderName = "gColourShininess";

    this->gDepth = std::make_shared<Texture2D>(screenDimentions.x, screenDimentions.y, GL_DEPTH_COMPONENT24);
    this->gDepth->shaderName = "gDepth";

    this->frameBuffer = std::make_unique<FrameBuffer>(GLFWHelper::getScreenWidth(),GLFWHelper::getScreenHeight());

    this->frameBuffer->transferToGbufferSupport(gPosition, gNormal,gColourAndShininess, gDepth);

    this->rendererType = COLOR_DEPTH_STENCIL;
    this->render_pass = SCENE_PASS;
    this->name = "Scene pass";
}

std::shared_ptr<Texture2D> ScenePass::render(std::shared_ptr<Scene> scene, std::shared_ptr<Renderer> renderer) {
    scene->renderingConstrains = NONE;
    renderer->setInputsForRenderPass(this->inputs);
    renderer->render(scene, this->frameBuffer);
    this->renderPassResult = this->frameBuffer->getRenderedResult();
    this->gRenderedScene = this->renderPassResult;
    this->gRenderedScene->shaderName = "gRenderedScene";

    return this->renderPassResult;
}

void ScenePass::renderUI() {
    RenderPass::renderUI();
    ImGui::Indent(20);
    ImVec2 imageSize(100,80);
    if(ImGui::TreeNode("G-Buffer")) {

        ImGui::SeparatorText("Position G buffer");
        ImGui::Image(reinterpret_cast<ImTextureID>(gPosition->ID),imageSize, ImVec2(0, 1),ImVec2(1, 0));

        ImGui::SeparatorText("Normal G buffer");
        ImGui::Image(reinterpret_cast<ImTextureID>(gNormal->ID), imageSize, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::SeparatorText("Colour and Shininess G buffer");
        ImGui::Image(reinterpret_cast<ImTextureID>(gColourAndShininess->ID), imageSize, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::TreePop();
    }


}

std::vector<std::shared_ptr<TextureBase>> ScenePass::getAdditionalOutputs() {
    std::vector<std::shared_ptr<TextureBase>> gBufferTextures ={
        this->gPosition,
        this->gNormal,
        this->gColourAndShininess,
        this->gRenderedScene,
        this->gDepth
    };
    return gBufferTextures;
}
