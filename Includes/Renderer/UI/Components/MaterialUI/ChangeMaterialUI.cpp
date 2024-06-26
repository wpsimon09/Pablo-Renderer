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
        displayExistingMaterials(ChangeMaterialUI::selectedID);
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

void ChangeMaterialUI::displayExistingMaterials(std::shared_ptr<Material> &_selectedID) {
    auto allMaterials = AssetsManager::getInstance()->getExistingMaterisl();
    int columnsTotal = 3;
    int displayedMaterial = 0;
    ImGui::SeparatorText("Existing materials");
    ImGui::Dummy(ImVec2(30,0));
    ImGui::BeginChild("Texture", ImVec2(300, 200));

    ImGui::SetItemTooltip(allMaterials[0]->getName().c_str());

    while(displayedMaterial != allMaterials.size()) {
        for (int col = 0; col < columnsTotal; col++) {
                if(displayedMaterial>=allMaterials.size())
                    break;
                if (col > 0)
                    ImGui::SameLine();

                auto material = allMaterials[displayedMaterial];

                ImVec2 imageSize (60,60);
                ImGui::SetItemAllowOverlap();
                if(material->getAlbedoTexture() != nullptr){

                    ImGui::GetWindowDrawList()->AddImage(
                        reinterpret_cast<ImTextureID>(material->getAlbedoTexture()->ID),
                        ImGui::GetCursorScreenPos(),
                        ImVec2(ImGui::GetCursorScreenPos().x + imageSize.x ,
                               ImGui::GetCursorScreenPos().y + imageSize.y ),
                        ImVec2(0, 1),
                        ImVec2(1, 0)
                    );
                }else {
                    auto albedo = material->getAlbedoColour();
                    ImVec2 p = ImGui::GetCursorScreenPos();
                    ImGui::GetWindowDrawList()->AddRectFilled(p, ImVec2(p.x + 60, p.y + 60), ImGui::GetColorU32(ImVec4(albedo.r, albedo.g, albedo.b,1.0f)));
                }

                if (ImGui::Selectable("##", material == _selectedID, 0, imageSize)) {
                    _selectedID = material;
                }
                ImGui::SetItemTooltip(material->getName().c_str());

            displayedMaterial++;

        }
    }
    ImGui::EndChild();
}
