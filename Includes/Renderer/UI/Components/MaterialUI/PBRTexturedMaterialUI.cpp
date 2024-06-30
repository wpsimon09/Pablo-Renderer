//
// Created by wpsimon09 on 30/06/24.
//

#include "PBRTexturedMaterialUI.h"
#include "Renderer/UI/Components/MaterialUI/ChangeSingleTextureUI.h"

void PBRTexturedMaterialUI::display(std::vector<std::shared_ptr<PBRMaterial<Texture2D>>> materialTextures) {
    for (auto &texture: materialTextures) {
        if(texture->type != nullptr && texture != nullptr && texture->type->wasFound){
            ImVec2 imageSize((float) 60, (float) 60);
            ImGui::BeginChild("ChangeSection");
            ImGui::Image(reinterpret_cast<ImTextureID>(texture->type->ID), imageSize);
            ImGui::SameLine(imageSize.x + 20);
            ImGui::Text(texture->shaderName.c_str());
            if(ImGui::Button("Change")) {
                selectedMaterial = texture;
                canOpenChangeUI = true;
            }
            ImGui::EndChild();
        }
    }
    if(canOpenChangeUI)
        ChangeSingleTextureUI::display(selectedMaterial, selectedMaterial->material_type);
}
