//
// Created by wpsimon09 on 20/04/24.
//

#include "MaterialUI.h"

void MaterialUI::display(int posX, int posY, int width, int height) {
    MaterialUI::posX = posX;
    MaterialUI::poxY = posY;
    MaterialUI::width = width;
    MaterialUI::height = height;

    ImGui::Text("Material");
    ImGui::BeginChild("Material", ImVec2(width, height), true);
    if(material!= nullptr && material->getAlbedoTexture()!= nullptr){
        ImVec2 imageSize((float)material->getAlbedoTexture()->texWidth/4, (float)material->getAlbedoTexture()->texHeight/4);
        ImGui::GetWindowDrawList()->AddImage(

                (void *)material->getAlbedoTexture()->ID,
                ImGui::GetCursorScreenPos(), // Use cursor screen position as top-left corner
                ImVec2(ImGui::GetCursorScreenPos().x + imageSize.x/4, ImGui::GetCursorScreenPos().y + imageSize.y/4), // Use bottom-right corner
                ImVec2(0, 1),
                ImVec2(1, 0)
        );
    }
    ImGui::EndChild();

}
