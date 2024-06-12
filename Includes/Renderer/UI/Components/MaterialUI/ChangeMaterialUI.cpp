//
// Created by wpsimon09 on 09/06/24.
//

#include "ChangeMaterialUI.h"
#include "Renderer/UI/Components/RenderableCreateationUI/FIleWindowUI/FileWindowUI.h"

void ChangeMaterialUI::display(Renderable* renderable) {
    ImGui::Begin("Change the material");
        ImGui::SetWindowSize(ImVec2(400, 400));
        ImGui::Text("Select material");
        if(ImGui::BeginCombo("Material", material[selectedMaterial].c_str())){
            for(int i = 0; i<2; i++){
                if(ImGui::Selectable(material[i].c_str(), selectedMaterial==i)){
                    selectedMaterial = (MATERIAL)i;
                }
            }

            ImGui::EndCombo();
        }

        if(selectedMaterial == COLOR){
            ImGui::SetNextItemWidth(200);
            ImGui::ColorPicker3("Material color", &color.x, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs);
        }
        else if (selectedMaterial == PBR_TEXTURE_MAPS){
            ChangeMaterialUI::texturesDirectory = FileWindowUI::display(true);
            ImGui::Text("Selected texture directory:");
            ImGui::BeginChild("Path",ImVec2(300, 40));
            ImGui::Text(ChangeMaterialUI::texturesDirectory.c_str());
            ImGui::EndChild();
        }

        if(ImGui::Button("Cancel")){
            MaterialUI::displayChangeMaterialUI = false;
        }
    ImGui::End();
}
