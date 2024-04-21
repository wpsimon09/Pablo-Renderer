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
    ImGui::SetWindowSize(ImVec2(400, 400));

    if (ImGui::Button("X")) {
        SceneMenu::showRendererCreation = false;
    }
    if (ImGui::Button("Open File Dialog")) {
        IGFD::FileDialogConfig config;
        config.path = ".";
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".gltf,.obj,.glb", config);
    }
    // display
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            ImGui::SetNextWindowFocus();
            ImGui::SetNextWindowSize(ImVec2(600,600));
            ImGui::SetNextWindowFocus();
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            std::string filePath = ImGuiFileDialog::Instance()->GetCurrentPath();


            auto renderable = std::make_unique<ModelSceneNode>(filePathName);
            PabloRenderer::getInstance()->getScene()->add(std::move(renderable));

        }

        ImGui::End();

        // close
        ImGuiFileDialog::Instance()->Close();
    }
    else
        ImGui::End();


}

