//
// Created by wpsimon09 on 26/06/24.
//

#include "ChangeSingleTextureUI.h"

void ChangeSingleTextureUI::display(std::shared_ptr<PBRTextured> materialToChange,
    MATERIAL_TEXTURE_TYPE textureToChange) {

    /*
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
            if(image->wasFound) {
                ImGui::SetItemAllowOverlap();
                ImGui::GetWindowDrawList()->AddImage(
                        reinterpret_cast<ImTextureID>(image->ID),
                        ImGui::GetCursorScreenPos(),
                        ImVec2(ImGui::GetCursorScreenPos().x + imageSize.x ,
                               ImGui::GetCursorScreenPos().y + imageSize.y ),
                        ImVec2(0, 1),
                        ImVec2(1, 0)
                );

                if (ImGui::Selectable("##", image->ID == selectedID, 0, imageSize)) {
                    selectedID = image->ID;
                }
                ImGui::SetItemTooltip(image->getFullPath().c_str());
            }
            displayedImage++;

        }
    }
    ImGui::EndChild();*/
}
