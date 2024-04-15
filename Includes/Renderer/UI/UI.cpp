//
// Created by wpsimon09 on 15/04/24.
//

#include "UI.h"


void UI::render() {
    bool shadow_demo_window = true;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow(&shadow_demo_window);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::init(GLFWwindow *window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    imGuiIo = &ImGui::GetIO();
    (void)imGuiIo;
    imGuiIo->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    imGuiIo->ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    ImGui::StyleColorsDark();
    const char* glsl_version = "#version 130";
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

template<class T>
void UI::setShaderValue(std::shared_ptr<Shader> shader, T value) {

}
