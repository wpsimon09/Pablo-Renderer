//
// Created by wpsimon09 on 26/06/24.
//

#include "ChangeSingleTextureUI.h"
#include "PBRTexturedMaterialUI.h"
void ChangeSingleTextureUI::display(std::shared_ptr<PBRMaterial<Texture2D>> &materialToChange,
    MATERIAL_TEXTURE_TYPE textureToChange) {
        ImGui::Begin("Change texture");
        ImGui::SetWindowSize(ImVec2(350, 260));
        auto allTextures = AssetsManager::getInstance()->getLoadedTextures();
        int rowsTotal = allTextures.size() / 3;
        int columnsTotal = 3;
        int displayedImage = 0;
        ImGui::SeparatorText("Loaded textures");
        ImGui::Dummy(ImVec2(30,0));
        ImGui::BeginChild("Texture", ImVec2(300, 200));

        ImGui::SetItemTooltip(allTextures[0]->getFullPath().c_str());

        while(displayedImage != allTextures.size()) {
            for (int col = 0; col < columnsTotal; col++) {
                if(displayedImage>=allTextures.size())
                    break;
                if (col > 0)
                    ImGui::SameLine();

                auto image = allTextures[displayedImage];

                ImVec2 imageSize (60,60);
                if(image->wasFound && image != nullptr) {
                    ImGui::SetItemAllowOverlap();
                    ImGui::GetWindowDrawList()->AddImage(
                            reinterpret_cast<ImTextureID>(image->ID),
                            ImGui::GetCursorScreenPos(),
                            ImVec2(ImGui::GetCursorScreenPos().x + imageSize.x ,
                                   ImGui::GetCursorScreenPos().y + imageSize.y ),
                            ImVec2(0, 1),
                            ImVec2(1, 0)
                    );
                    std::string label = image->shaderName + std::to_string(image->ID);
                    if (ImGui::Selectable(label.c_str(), image == selectedID, 0, imageSize)) {
                        selectedID = image;
                    }
                    ImGui::SetItemTooltip(image->getFullPath().c_str());
                }
                displayedImage++;
            }
        }
        ImGui::EndChild();

        ImGui::NewLine();

        if(ImGui::Button("Apply")) {
            if(selectedID != nullptr) {
                materialToChange->type = selectedID;
                PBRTexturedMaterialUI::canOpenChangeUI = false;
            }

        }

        ImGui::SameLine();

        if(ImGui::Button("Cancel")) {
            PBRTexturedMaterialUI::canOpenChangeUI = false;
        }

        ImGui::End();
}
