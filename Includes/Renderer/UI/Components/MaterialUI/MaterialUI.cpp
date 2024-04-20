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
    if(material!= nullptr){
        ImGui::Text("Material Selecte: %d", material->shader->name.c_str());
    }
    ImGui::EndChild();

}
