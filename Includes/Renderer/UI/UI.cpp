//
// Created by wpsimon09 on 15/04/24.
//

#include "UI.h"



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

void UI::render() {
    bool shadow_demo_window = true;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    static float f = 0.0f;
    static int counter = 0;


    //-------------------------
    // MAIN APPLICATION WINDOW
    //-------------------------

        ImGui::Begin("Tools",NULL,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );
            ImGui::SetWindowPos(ImVec2(0,0));
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / imGuiIo->Framerate, imGuiIo->Framerate);
            ImGui::SetWindowSize(ImVec2(300,(float)GLFWHelper::getScreenHeight()));
        ImGui::End();

        ImGui::Begin("ViewPort",NULL,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );
            ImGui::SetWindowPos(ImVec2(300,0));
            ImGui::SetWindowSize(ImVec2((float)GLFWHelper::getScreenWidth() - 300,(float)GLFWHelper::getScreenHeight()));
            ImGui::GetWindowDrawList()->AddImage(
            (void *)renderedScene->ID,
            ImVec2(300, 0),
            ImVec2((float)renderedScene->texWidth, (float)renderedScene->texHeight),
            ImVec2(0, 1),
            ImVec2(1, 0)
            );
        ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void UI::terminate() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

template<class T>
void UI::setShaderValue(std::shared_ptr<Shader> shader, T value) {

}
