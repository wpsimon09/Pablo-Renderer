//
// Created by wpsimon09 on 03/07/24.
//

#include "MenuBarUI.h"

#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"


void MenuBarUI::display() {
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("Edit"))
    {
        if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
        if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
        ImGui::Separator();
        if (ImGui::MenuItem("Cut", "CTRL+X")) {}
        if (ImGui::MenuItem("Copy", "CTRL+C")) {}
        if (ImGui::MenuItem("Paste", "CTRL+V")) {}
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
}
