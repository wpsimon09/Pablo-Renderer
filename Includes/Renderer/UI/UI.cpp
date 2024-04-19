//
// Created by wpsimon09 on 15/04/24.
//

#include "UI.h"
#include "Renderer/UI/Components/SceneMenu/SceneMenu.h"
#include "Renderer/UI/Components/ViewPort/ViewPort.h"

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
        SceneMenu::debugTexture = debugTexture;
        SceneMenu::display(0,10,500);
        //------------
        // VIEW PORT
        //-----------
        ViewPort::renderedScene = renderedScene;
        ViewPort::display(500,10, GLFWHelper::getScreenWidth(500), GLFWHelper::getScreenHeight(200));

        ImGui::Begin("Application info",NULL,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );
            ImGui::SetWindowSize(ImVec2((float)GLFWHelper::getScreenWidth(), 200));
            ImGui::SetWindowPos(ImVec2(0,(float)GLFWHelper::getScreenHeight()-190 ));
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / imGuiIo->Framerate, imGuiIo->Framerate);
            if(ImGui::Button("Add")){
                auto cube = std::make_shared<CubeGeometry>();
                auto gold = std::make_shared<PBRTextured>("Assets/Textures/PBR/Gold", true);
                auto renderable = std::make_unique<Renderable>(cube, gold);
                renderable->recievesShadow = true;
                PabloRenderer::getInstance()->getScene()->add(std::move(renderable));
            }
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
