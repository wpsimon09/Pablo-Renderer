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
            ImGui::SetWindowSize(ImVec2(500,(float)GLFWHelper::getScreenHeight(200)));

            if(ImGui::TreeNode("Positions")){
                ImGui::SliderAngle("Rotation", &f);

                ImGui::TreePop(); // Close the folder
            };

            if(ImGui::TreeNode("Debug texture")){
                ImGui::BeginChild("DebugTexture");
                ImVec2 imageSize((float)debugTexture->texWidth, (float)debugTexture->texHeight);
                ImGui::GetWindowDrawList()->AddImage(

                (void *)debugTexture->ID,
                        ImGui::GetCursorScreenPos(), // Use cursor screen position as top-left corner
                        ImVec2(ImGui::GetCursorScreenPos().x + imageSize.x/4, ImGui::GetCursorScreenPos().y + imageSize.y/4), // Use bottom-right corner
                        ImVec2(0, 1), // Top-left UV coordinate
                        ImVec2(1, 0)  // Bottom-right UV coordinate
                );

                ImGui::TreePop(); // Close the folder
            };


        ImGui::End();

        //------------
        // VIEW PORT
        //-----------
        ImGui::Begin("ViewPort",NULL,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );
            ImGui::SetWindowPos(ImVec2(510,0));
            ImGui::SetWindowSize(ImVec2((float)GLFWHelper::getScreenWidth(20) - 300,(float)GLFWHelper::getScreenHeight(200)));
            ImGui::GetWindowDrawList()->AddImage(
            (void *)renderedScene->ID,
            ImVec2(300, 0),
            ImVec2((float)renderedScene->texWidth, (float)renderedScene->texHeight),
            ImVec2(0, 1),
            ImVec2(1, 0)
            );

        ImGui::End();

        ImGui::Begin("Application info",NULL,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );
            ImGui::SetWindowSize(ImVec2((float)GLFWHelper::getScreenWidth(), 200));
            ImGui::SetWindowPos(ImVec2(0,(float)GLFWHelper::getScreenHeight()-190 ));
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / imGuiIo->Framerate, imGuiIo->Framerate);
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
