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

    ImVec2 imageSize((float) iblPiplineInstance->getHDR()->texWidth / 12, (float) iblPiplineInstance->getHDR()->texHeight / 12);
        ImGui::BeginChild("HDRPreview", imageSize, true);
        ImGui::GetWindowDrawList()->AddImage(
                (void *) iblPiplineInstance->getHDR()->ID,
                ImGui::GetCursorScreenPos(), // Use cursor screen position as top-left corner
                ImVec2(ImGui::GetCursorScreenPos().x + imageSize.x ,
                       ImGui::GetCursorScreenPos().y + imageSize.y ), // Use bottom-right corner
                ImVec2(0, 1),
                ImVec2(1, 0)
        );
        ImGui::EndChild();

    instance->getScene()->getSkyBox().renderUI();
    //--------------------------
    // LOADING NEW IBL PIPELINE
    //--------------------------
    FileWindowUI::supportedFiles = ".hdr";
    EnviromentUI::hdrTexturePath = FileWindowUI::display();
    if(!hdrTexturePath.empty()){
        try{
            iblPiplineInstance->calculatePreview(hdrTexturePath.c_str());
        }catch (std::exception &e){
            ImGui::Text(e.what());
        }
    }

    if(ImGui::Button("Apply")){
        try{
            iblPiplineInstance->recalculateIBL();
            SceneMenu::showEnviromentMenu = false;
            instance->getScene()->getSkyBox().setSkyBoxTexture(iblPiplineInstance->iblTextures[0]->type);
        }catch (std::exception &e){

            ImGui::Text(e.what());
        }
    }

    ImGui::SameLine();

    if(ImGui::Button("Close")){
        SceneMenu::showEnviromentMenu = false;
    }

    ImGui::End();
}
