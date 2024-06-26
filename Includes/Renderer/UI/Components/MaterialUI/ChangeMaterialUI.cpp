//
// Created by wpsimon09 on 09/06/24.
//

#include "ChangeMaterialUI.h"
#include "Renderer/UI/Components/RenderableCreateationUI/FIleWindowUI/FileWindowUI.h"
#include "Renderer/Utils/AssetsManager/AssetsManager.h"

void ChangeMaterialUI::display(Renderable *renderable) {
    ImGui::Begin("Change the material");
    ImGui::SetWindowSize(ImVec2(400, 400));
    ImGui::Text("Select material");
    if (ImGui::BeginCombo("Material", material[selectedMaterial].c_str())) {
        for (int i = 0; i < 2; i++) {
            if (ImGui::Selectable(material[i].c_str(), selectedMaterial == i)) {
                selectedMaterial = (MATERIAL) i;
            }
        }

        ImGui::EndCombo();
    }

    if (selectedMaterial == PBR_TEXTURE_MAPS) {
        auto allTextures = AssetsManager::getInstance()->getLoadedTextures();
        int rowsTotal = allTextures.size() / 3;
        int columnsTotal = 3;
        int displayedImage = 0;
        ImGui::SeparatorText("Loaded textures");
        ImGui::Dummy(ImVec2(10,0));
        ImGui::BeginChild("Texture", ImVec2(300, 200));

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
                    ImGui::SetItemTooltip(image->getFullPath().c_str());
                    ImGui::GetWindowDrawList()->AddImage(
                            reinterpret_cast<ImTextureID>(image->ID),
                            ImGui::GetCursorScreenPos(),
                            ImVec2(ImGui::GetCursorScreenPos().x + imageSize.x ,
                                   ImGui::GetCursorScreenPos().y + imageSize.y ),
                            ImVec2(0, 1),
                            ImVec2(1, 0)
                    );

                    if (ImGui::Selectable("##", false, 0, imageSize)) {
                    }
                }
                displayedImage++;
            }
        }
        ImGui::EndChild();
    }

    ImGui::NewLine();
    if (ImGui::Button("Apply")) {
        if (selectedMaterial == COLOR) {
            renderable->setMaterial(std::make_shared<PBRColor>());
        } else if (selectedMaterial == PBR_TEXTURE_MAPS) {
        }
    }

    if (ImGui::Button("Cancel")) {
        MaterialUI::displayChangeMaterialUI = false;
    }
    ImGui::End();
}
