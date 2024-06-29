//
// Created by wpsimon09 on 19/04/24.
//

#include "SceneMenu.h"
#include "Renderer/UI/Components/MaterialUI/MaterialUI.h"
#include "Renderer/UI/Components/SceneNodeUI/SceneNodeUI.h"
#include "Renderer/UI/Components/LightUI/LightUI.h"
#include "Renderer/UI/Components/RenderableCreateationUI/RenderableCreationUI.h"
#include "Renderer/UI/Components/RenderGraphUI/RenderGraphUI.h"
#include "Renderer/UI/Components/EnviromentUI/EnviromentUI.h"
#include <algorithm>
// recursion counting mechanism for selecting right renderables
int i = 0;

void SceneMenu::display(int posX, int posY, int width, int height) {
    //reset recursion counting each frame
    i = 0;


    Component::posX = posX;
    Component::poxY = posY;
    Component::width = width;
    Component::height = height;

    ImGui::Begin("Scene", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::SetWindowPos(ImVec2((float) posX, (float) posY));
    ImGui::SetWindowSize(ImVec2((float) width, (float) height/2));
    ImGui::SeparatorText("Scene");
    ImGui::BeginChild("Scene", ImVec2((float) width - 20, (float) GLFWHelper::getScreenHeight() / 2 - 120), true,
                      ImGuiWindowFlags_HorizontalScrollbar);

    //display sthe entire scene graph structure
    displaySceneNodeMenu(*PabloRenderer::getInstance()->getScene()->root);

    selectedSceneNode = PabloRenderer::getInstance()->getScene()->getSelectedNodeID();

    ImGui::EndChild();

    if(ImGui::Button("Add new")){
        showRendererCreation = true;
    }

    ImGui::SameLine();

    if(ImGui::Button("Enviroment settings")){
        showEnviromentMenu = true;
    }



    ImGui::NewLine();
    ImGui::End();
    ImGui::Begin("Tools", NULL,  ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::SetWindowPos(ImVec2((float) posX, (float) posY + (height/2)));
    ImGui::SetWindowSize(ImVec2((float) width, (float) height/2));
    if (ImGui::BeginTabBar("Renderable properties"))
    {
        if (ImGui::BeginTabItem("Material"))
        {
            MaterialUI::display(width - 20, 0, width);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Light"))
        {
            LightUI::display(width - 20, 0, width);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Transformation"))
        {
            SceneNodeUI::display();
            ImGui::EndTabItem();
        }
        if(ImGui::BeginTabItem("Render graph")){
            RenderGraphUI::display(width - 20, 0, width, 0);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }

    ImGui::End();

    if(showRendererCreation){
        RenderableCreationUI::display();
    }

    if (showEnviromentMenu){
        EnviromentUI::display();
    }
}

    void SceneMenu::displaySceneNodeMenu(SceneNode &sceneNode, int indentLevel) {

    for (int i = 0; i < indentLevel; ++i) {
        ImGui::Indent();
    }

    auto& renderable = sceneNode.getRenderable();
    if (renderable != nullptr) {
        auto name = renderable->name;
        name += " " + std::to_string(static_cast<int>(sceneNode.getID()));
        if (name.empty()) {
            name = "##";
        }
        if (ImGui::Selectable(name.c_str(), selectedSceneNode == sceneNode.getID()) || sceneNode.getID() == selectedSceneNode) {
            selectedSceneNode = sceneNode.getID();
            sceneNode.isSelected = true;
            MaterialUI::renderable = sceneNode.getRenderable().get();
            SceneNodeUI::sceneNode = &sceneNode;
        } else {
            sceneNode.isSelected = false;
        }
    }

    for (auto& childNode : sceneNode.getChildren()) {
        displaySceneNodeMenu(*childNode, indentLevel + 1);
    }

    for (int i = 0; i < indentLevel; ++i) {
        ImGui::Unindent();
    }
    }
