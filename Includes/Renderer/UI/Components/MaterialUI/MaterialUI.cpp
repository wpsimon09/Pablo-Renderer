//
// Created by wpsimon09 on 20/04/24.
//

#include "MaterialUI.h"
#include "Renderer/UI/Components/MaterialUI/ChangeMaterialUI.h"

void MaterialUI::display(int posX, int posY, int width, int height) {
    MaterialUI::posX = posX;
    MaterialUI::poxY = posY;
    MaterialUI::width = width;
    MaterialUI::height = height;

    ImGui::Text("Material");

        if(renderable != nullptr){
            renderable->getObjectMaterial()->renderUI();

            if(ImGui::Button("Change")){
                displayChangeMaterialUI = true;
            }

            if(displayChangeMaterialUI){
                if(renderable != nullptr){
                    ChangeMaterialUI::display(renderable);
                }
            }
        }
        else
            ImGui::Text("No item selected please select one from the SceneStructure");
}
