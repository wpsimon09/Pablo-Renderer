//
// Created by wpsimon09 on 30/06/24.
//

#include "PBRTexturedMaterialUI.h"
#include "Renderer/UI/Components/MaterialUI/ChangeSingleTextureUI.h"

void PBRTexturedMaterialUI::display(std::vector<std::shared_ptr<PBRMaterial<Texture2D>>> materialTextures) {
    for (auto &texture: materialTextures) {
        if(texture->type != nullptr && texture != nullptr && texture->type->wasFound){
            ImGui::SeparatorText(texture->shaderName.c_str());
            ImVec2 imageSize((float) 60, (float) 60);
            ImGui::Image(reinterpret_cast<ImTextureID>(texture->type->ID), imageSize);
            ImGui::SameLine(imageSize.x + 20);
            std::string label = "Change ##" + texture->shaderName;
            ImGui::Dummy(ImVec2(0,10));
            if(ImGui::Button(label.c_str())) {
                selectedMaterial = texture;
                canOpenChangeUI = true;
            }
            ImGui::Dummy(ImVec2(0, 15));
        }
    }
    if(canOpenChangeUI)
        ChangeSingleTextureUI::display(selectedMaterial, selectedMaterial->material_type);
}
