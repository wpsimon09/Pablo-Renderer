//
// Created by wpsimon09 on 23/05/24.
//

#include "EnviromentUI.h"
#include "Renderer/UI/Components/RenderableCreateationUI/FIleWindowUI/FileWindowUI.h"
#include "Renderer/UI/Components/SceneMenu/SceneMenu.h"
#include "Renderer/PabloRenderer.h"

void EnviromentUI::display() {
    ImGui::Begin("Environment settings");

    ImGui::SetWindowSize(ImVec2(400, 400));

    auto instance = PabloRenderer::getInstance();
    FileWindowUI::supportedFiles = ".hdr";
    FileWindowUI::display();

    if(ImGui::Button("Close")){
        SceneMenu::showEnviromentMenu = false;
    }

    ImGui::End();
}
