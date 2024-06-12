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

        if(ImGui::Button("Apply")){
            if(selectedMaterial == COLOR){
                renderable->setMaterial(std::make_shared<PBRColor>());
            }
            else if (selectedMaterial == PBR_TEXTURE_MAPS){
            }

        }

        if(ImGui::Button("Cancel")){
            MaterialUI::displayChangeMaterialUI = false;
        }
    ImGui::End();
}
