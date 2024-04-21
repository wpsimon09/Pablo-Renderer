//
// Created by wpsimon09 on 15/04/24.
//

#include "UI.h"
#include "Renderer/UI/Components/SceneMenu/SceneMenu.h"
#include "Renderer/UI/Components/ViewPort/ViewPort.h"
#include "Renderer/UI/Components/BottomMenu/BottomMenu.h"
#include "Renderer/UI/Components/LightUI/LightUI.h"

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

        //-------------------------
        // TOOLS
        //-------------------------
        LightUI::debugTexture = debugTexture;
        SceneMenu::display(0,10,500, GLFWHelper::getScreenHeight(10));

        //------------
        // VIEW PORT
        //-----------
        ViewPort::renderedScene = renderedScene;
        ViewPort::imGuiIo = imGuiIo;
        ViewPort::display(500,10, GLFWHelper::getScreenWidth(500), GLFWHelper::getScreenHeight(10));

        //-----------
        //BOTTOM MENU
        //-----------
        //BottomMenu::display(0,GLFWHelper::getScreenHeight(190), GLFWHelper::getScreenWidth(), 200 );


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
