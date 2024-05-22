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

    ImGui::BeginChild("Material");
        if(material != nullptr){
            material->renderUI();
        }
        else
            ImGui::Text("No item selected please select one from the SceneStructure");
    ImGui::EndChild();


}
