//
// Created by wpsimon09 on 21/04/24.
//

#include "RenderableCreationUI.h"
#include "Renderer/PabloRenderer.h"
#include "Renderer/UI/Components/SceneMenu/SceneMenu.h"
#include "Renderer/SceneGraph/ModelSceneNode/ModelSceneNode.h"

void RenderableCreationUI::display() {
    ImGui::SetNextWindowFocus();

    ImGui::Begin("Add renderable", nullptr);
    ImGui::SetWindowSize(ImVec2(400,400));

    if(ImGui::Button("X")){
        SceneMenu::showRendererCreation = false;
    }
    if(ImGui::Button("Add")){
        auto material = std::make_shared<PBRTextured>("Assets/Textures/PBR/Gold", true);
        auto geometry = std::make_unique<ModelSceneNode>("Assets/Model/pot/brass_pot_01_2k.gltf");
        //auto renderable = std::make_unique<Renderable>(geometry, material);
        PabloRenderer::getInstance()->getScene()->add(std::move(geometry));
    }

    ImGui::End();
}
