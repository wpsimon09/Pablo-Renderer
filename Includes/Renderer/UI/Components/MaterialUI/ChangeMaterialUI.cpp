//
// Created by wpsimon09 on 09/06/24.
//

#include "ChangeMaterialUI.h"
#include "Renderer/UI/Components/RenderableCreateationUI/FIleWindowUI/FileWindowUI.h"
#include "Renderer/UI/UIHelpers/UIHelper.h"
#include "Renderer/Utils/AssetsManager/AssetsManager.h"

void ChangeMaterialUI::display(Renderable *renderable) {
    ImGui::Begin("Change the material");
    ImGui::Text("Select material");
    if (ImGui::BeginCombo("Material", material[selectedMaterial].c_str())) {
        for (int i = 0; i < 3; i++) {
            if (ImGui::Selectable(material[i].c_str(), selectedMaterial == i)) {
                selectedMaterial = (MATERIAL) i;
            }
        }

        ImGui::EndCombo();
    }

    UIHelper::displayExistingMaterials(ChangeMaterialUI::selectedID, selectedMaterial);

    ImGui::Dummy(ImVec2(0,50));

    ImGui::Separator();

    if(ImGui::Button("Create new material")) {
        canShowCreationOfNewMaterial = true;
    }

    if(canShowCreationOfNewMaterial) {
        displayCreateNewMaterial();
    }

    ImGui::Separator();

    ImGui::Dummy(ImVec2(0,20));

    ImGui::NewLine();

    ImGui::SetNextItemShortcut(ImGuiKey_Enter);
    if (ImGui::Button("Apply")) {
        if (selectedID != nullptr) {
            AssetsManager::getInstance()->storeMaterial(selectedID);
            renderable->setMaterial(selectedID);
        }
    }

    if (ImGui::Button("Cancel")) {
        MaterialUI::displayChangeMaterialUI = false;
    }
    ImGui::End();
}


void ChangeMaterialUI::displayCreateNewMaterial() {
    ImGui::Begin("Create new material");
    if (ImGui::BeginCombo("Material", material[selectedMaterialForCreation].c_str())) {
        for (int i = 0; i < 2; i++) {
            if (ImGui::Selectable(material[i].c_str(), selectedMaterialForCreation == i)) {
                selectedMaterialForCreation = (MATERIAL) i;
            }
        }
        ImGui::EndCombo();
    }
    ImGui::InputText("Name", nameOfTheMaterial, 64);

        if(selectedMaterialForCreation == PBR_TEXTURE_MAPS) {
            ImGui::Dummy(ImVec2(0, 30));
            ImGui::SeparatorText("Select directory with texture maps");
            texturesDirectory = FileWindowUI::display(true);
            ImGui::SameLine();
            ImGui::Text("(?)");
            ImGui::SetItemTooltip("Texture maps must be named albedo.png, normal.png and arm.png for it to load properly");

            ImGui::Dummy(ImVec2(0, 30));
            ImGui::SeparatorText("Additional properties");
            ImGui::Checkbox("Supports area light", &supportsAreaLight);

            if(!texturesDirectory.empty()) {
                selectedID = std::make_shared<PBRTextured>(supportsAreaLight,texturesDirectory, false, nameOfTheMaterial);
            }

            if(selectedID != nullptr) {
                ImGui::Dummy(ImVec2(0, 30));
                ImGui::SeparatorText("Preview");
                ImGui::Image(reinterpret_cast<ImTextureID>(selectedID->getAlbedoTexture()->ID), ImVec2(70,70));
            }

            ImGui::Dummy(ImVec2(0, 10));

            if(ImGui::Button("Create")) {
                if(selectedID !=nullptr) {
                    selectedID->setAreaLightSupport(supportsAreaLight);
                    AssetsManager::getInstance()->storeMaterial(selectedID);
                    canShowCreationOfNewMaterial = false;
                }
            }

            ImGui::SameLine();

            if(ImGui::Button("Cancel")) {
                selectedID = nullptr;
                canShowCreationOfNewMaterial = false;
            }
        }

    ImGui::End();
}
