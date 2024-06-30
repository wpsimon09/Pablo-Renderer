//
// Created by wpsimon09 on 30/06/24.
//

#include "PBRTexturedMaterialUI.h"

void PBRTexturedMaterialUI::display(std::vector<std::shared_ptr<PBRMaterial<Texture2D>>> materialTextures) {
    std::shared_ptr<PBRMaterial<Texture2D>> selectedMaterial;
    for (auto &texture: materialTextures) {
        if(texture->type != nullptr && texture != nullptr && texture->type->wasFound){
            ImVec2 imageSize((float) 60, (float) 60);
            ImGui::BeginChild("ChangeSection");
            ImGui::Image(reinterpret_cast<ImTextureID>(texture->type->ID), imageSize);
            ImGui::SameLine(imageSize.x + 20);
            ImGui::Text(texture->shaderName.c_str());
            if(ImGui::Button("Change")) {
                selectedMaterial = texture;
                            }
            ImGui::EndChild();
        }
    }
        //ChangeSingleTextureUI::display(selectedMaterial, selectedMaterial->material_type);
}
