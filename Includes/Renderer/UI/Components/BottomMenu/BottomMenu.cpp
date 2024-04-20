//
// Created by wpsimon09 on 19/04/24.
//

#include "BottomMenu.h"

void BottomMenu::display(int posX, int posY, int width, int height) {
    Component::posX = posX;
    Component::poxY = posY;
    Component::width = width;
    Component::height = height;

    ImGui::Begin("Application info",NULL,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );
    ImGui::SetWindowSize(ImVec2((float)width, height));
    ImGui::SetWindowPos(ImVec2(posX,(float)posY ));

    ImGui::NewLine();
    ImGui::Text("Material");
    ImGui::BeginChild("Material", ImVec2(width-10, height-10), true);


    ImGui::EndChild();

    ImGui::End();
}
