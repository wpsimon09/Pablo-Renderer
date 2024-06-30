//
// Created by wpsimon09 on 19/04/24.
//

#include "ViewPort.h"

void ViewPort::display(int posX, int posY, int width, int height) {
    Component::posX = posX;
    Component::poxY = posY;
    Component::width = width;
    Component::height = height;

    ImGui::Begin("ViewPort",NULL,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );
    ImGui::SetWindowPos(ImVec2(posX,posY));
    ImGui::SetWindowSize(ImVec2((float)width,(float)height));
    ImGui::Text(" %.3f ms/frame (%.1f FPS)", 1000.0f / imGuiIo->Framerate, imGuiIo->Framerate);
    ImVec2 imageSize((float) width-20, (float) height - 53);
    ImGui::Image(reinterpret_cast<ImTextureID>(renderedScene->ID), imageSize, ImVec2(0, 1),ImVec2(1, 0));
    if(ImGui::IsWindowHovered()){
        GLFWHelper::canProcessMouse = true;
    }else
        GLFWHelper::canProcessMouse = false;
    ImGui::End();

}
