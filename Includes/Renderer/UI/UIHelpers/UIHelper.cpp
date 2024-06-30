//
// Created by wpsimon09 on 30/06/24.
//

#include "UIHelper.h"
#include "imgui.h"
#include "Renderer/Utils/AssetsManager/AssetsManager.h"


void UIHelper::displayExistingMaterials(std::shared_ptr<Material> &_selectedID, MATERIAL mat) {
    auto allMaterials = AssetsManager::getInstance()->getExistingMaterisl(mat);
    int columnsTotal = 3;
    int displayedMaterial = 0;
    ImGui::BeginChild("Texture", ImVec2(300, 200));

    ImGui::SeparatorText("Existing materials");
    ImGui::Dummy(ImVec2(30, 0));

    ImGui::SetItemTooltip(allMaterials[0]->getName().c_str());

    while (displayedMaterial != allMaterials.size()) {
        for (int col = 0; col < columnsTotal; col++) {
            if (displayedMaterial >= allMaterials.size())
                break;
            if (col > 0)
                ImGui::SameLine();

            auto material = allMaterials[displayedMaterial];

            ImVec2 imageSize(60, 60);
            ImGui::SetItemAllowOverlap();
            if (material->getAlbedoTexture() != nullptr) {
                ImGui::GetWindowDrawList()->AddImage(
                    reinterpret_cast<ImTextureID>(material->getAlbedoTexture()->ID),
                    ImGui::GetCursorScreenPos(),
                    ImVec2(ImGui::GetCursorScreenPos().x + imageSize.x,
                           ImGui::GetCursorScreenPos().y + imageSize.y),
                    ImVec2(0, 1),
                    ImVec2(1, 0)
                );
            } else {
                auto albedo = material->getAlbedoColour();
                ImVec2 p = ImGui::GetCursorScreenPos();
                ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + 60, p.y + 60),
                                                          ImGui::GetColorU32(
                                                              ImVec4(albedo.r, albedo.g, albedo.b, 1.0f)));
            }
            std::string identifier = "##" + std::to_string(material->getID());
            if (ImGui::Selectable(identifier.c_str(), material == _selectedID, 0, imageSize)) {
                _selectedID = material;
            }
            ImGui::SetItemTooltip(material->getName().c_str());

            displayedMaterial++;
        }
    }
    ImGui::EndChild();
}

void UIHelper::displayExistingTextures(MATERIAL_TEXTURE_TYPE filter) {
}

template<typename T>
void UIHelper::displayItemsInGrid(std::vector<T> items) {

}
