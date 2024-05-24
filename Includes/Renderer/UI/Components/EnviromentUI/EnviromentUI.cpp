//
// Created by wpsimon09 on 23/05/24.
//

#include "EnviromentUI.h"
#include "Renderer/UI/Components/RenderableCreateationUI/FIleWindowUI/FileWindowUI.h"
#include "Renderer/UI/Components/SceneMenu/SceneMenu.h"
#include "Renderer/PabloRenderer.h"

void EnviromentUI::display() {
    auto instance = PabloRenderer::getInstance();
    auto iblPiplineInstance = instance->getScene()->getIblPipeLine();

    ImGui::Begin("Environment settings");

    ImGui::SetWindowSize(ImVec2(400, 400));

    ImGui::Text("Environment preview");

    ImVec2 imageSize((float) iblPiplineInstance->iblTextures[0]->type->texWidth / 4, (float) iblPiplineInstance->iblTextures[0]->type->texHeight / 4);
        ImGui::BeginChild("##", imageSize);
        ImGui::GetWindowDrawList()->AddImage(
                (void *) iblPiplineInstance->iblTextures[0]->type->ID,
                ImGui::GetCursorScreenPos(), // Use cursor screen position as top-left corner
                ImVec2(ImGui::GetCursorScreenPos().x + imageSize.x ,
                       ImGui::GetCursorScreenPos().y + imageSize.y ), // Use bottom-right corner
                ImVec2(0, 1),
                ImVec2(1, 0)
        );
        ImGui::EndChild();

    //--------------------------
    // LOADING NEW IBL PIPELINE
    //--------------------------
    EnviromentUI::hdrTexturePath = FileWindowUI::supportedFiles = ".hdr";
    FileWindowUI::display();



    if(ImGui::Button("Close")){
        SceneMenu::showEnviromentMenu = false;
    }

    ImGui::End();
}
