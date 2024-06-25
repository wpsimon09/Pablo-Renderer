//
// Created by wpsimon09 on 09/06/24.
//

#include "ChangeMaterialUI.h"
#include "Renderer/UI/Components/RenderableCreateationUI/FIleWindowUI/FileWindowUI.h"
#include "Renderer/Utils/AssetsManager/AssetsManager.h"

void ChangeMaterialUI::display(Renderable* renderable) {

    ImGui::Begin("Change the material");
        ImGui::SetWindowSize(ImVec2(400, 400));
        ImGui::Text("Select material");
        if(ImGui::BeginCombo("Material", material[selectedMaterial].c_str())){
            for(int i = 0; i<2; i++){
                if(ImGui::Selectable(material[i].c_str(), selectedMaterial==i)){
                    selectedMaterial = (MATERIAL)i;
                }
            }

            ImGui::EndCombo();
        }

        if(selectedMaterial == PBR_TEXTURE_MAPS) {
            auto allTextures = AssetsManager::getInstance()->getLoadedTextures();
            int sizeX = allTextures.size()/2;
            int sizeY = allTextures.size() - sizeX;
            for (int col = 0; col<sizeY; col++) {
                for (int row = 0; row<sizeX; row++ ) {
                    if(row > 0)
                        ImGui::SameLine();
                    ImGui::SetItemAllowOverlap();

                    if(ImGui::Selectable("Texture",false, 0, ImVec2(40,40))) {

                    }
                }
            }
        }

        if(ImGui::Button("Apply")){
            if(selectedMaterial == COLOR){
                renderable->setMaterial(std::make_shared<PBRColor>());
            }
            else if (selectedMaterial == PBR_TEXTURE_MAPS){
            }

        }

        if(ImGui::Button("Cancel")){
            MaterialUI::displayChangeMaterialUI = false;
        }
    ImGui::End();
}
