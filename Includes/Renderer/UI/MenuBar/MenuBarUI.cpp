//
// Created by wpsimon09 on 03/07/24.
//

#include "MenuBarUI.h"

#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"


void MenuBarUI::display() {
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("Edit"))
    {
        if (ImGui::MenuItem("Reload shaders", "R")) {ShaderManager::relodeShaders();}
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
}
