//
// Created by wpsimon09 on 19/04/24.
//

#include "BottomMenu.h"
#include "Renderer/UI/Components/MaterialUI/MaterialUI.h"

void BottomMenu::display(int posX, int posY, int width, int height) {
    Component::posX = posX;
    Component::poxY = posY;
    Component::width = width;
    Component::height = height;

    ImGui::Begin("Material",NULL,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );
    ImGui::SetWindowSize(ImVec2((float)width, height));
    ImGui::SetWindowPos(ImVec2(posX,(float)posY ));

    MaterialUI::display(posX, posY, width, height-80);

    ImGui::End();
}
