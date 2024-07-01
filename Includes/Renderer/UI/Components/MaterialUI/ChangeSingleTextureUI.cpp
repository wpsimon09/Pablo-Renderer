//
// Created by wpsimon09 on 26/06/24.
//

#include "ChangeSingleTextureUI.h"
#include "PBRTexturedMaterialUI.h"
#include "Renderer/UI/Components/RenderableCreateationUI/FIleWindowUI/FileWindowUI.h"
#include "Renderer/UI/UIHelpers/UIHelper.h"

void ChangeSingleTextureUI::display(std::shared_ptr<PBRMaterial<Texture2D> > &materialToChange,
                                    MATERIAL_TEXTURE_TYPE textureToChange) {
    ImGui::Begin("Change texture");
    ImGui::SetWindowSize(ImVec2(350, 460));

    UIHelper::displayExistingTextures(selectedID, textureToChange);

    ImGui::Separator();

    addTextureFromDirectory(textureToChange);

    ImGui::Separator();
    if (ImGui::Button("Apply")) {
        if (selectedID != nullptr) {
            materialToChange->type = selectedID;
            PBRTexturedMaterialUI::canOpenChangeUI = false;
            selectedID = nullptr;
            newTexturePath = "";
            newTexture = nullptr;
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Cancel")) {
        PBRTexturedMaterialUI::canOpenChangeUI = false;
        selectedID = nullptr;
        newTexturePath = "";
        newTexture = nullptr;
    }

    ImGui::End();
}

void ChangeSingleTextureUI::addTextureFromDirectory(MATERIAL_TEXTURE_TYPE textureType) {
    FileWindowUI::supportedFiles = ".png";
    newTexturePath = FileWindowUI::display();
    if (!newTexturePath.empty()) {
        newTexture = AssetsManager::getInstance()->getTexture(newTexturePath);
        selectedID = newTexture;
    }
}
