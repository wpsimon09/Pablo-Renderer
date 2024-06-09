//
// Created by wpsimon09 on 09/06/24.
//

#include "ChangeMaterial.h"
#include "Renderer/UI/Components/RenderableCreateationUI/FIleWindowUI/FileWindowUI.h"

void ChangeMaterial::display(std::shared_ptr<Renderable> renderable) {
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
        ImGui::ColorPicker3("Material color", &color.x, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs);
    }
    else if (selectedMaterial == TEXTURE){
        texturesDirectory = FileWindowUI::display(true);
        ImGui::Text("Selected texture directory:");
        ImGui::Text(texturesDirectory.c_str());
    }
}
