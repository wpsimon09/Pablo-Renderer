//
// Created by wpsimon09 on 19/04/24.
//

#include "SceneMenu.h"
#include "Renderer/UI/Components/MaterialUI/MaterialUI.h"
#include "Renderer/UI/Components/SceneNodeUI/SceneNodeUI.h"
#include "Renderer/UI/Components/LightUI/LightUI.h"
#include "Renderer/UI/Components/RenderableCreateationUI/RenderableCreationUI.h"
#include <algorithm>

void SceneMenu::display(int posX, int posY, int width, int height) {
    Component::posX = posX;
    Component::poxY = posY;
    Component::width = width;
    Component::height = height;

    ImGui::Begin("Tools", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::SetWindowPos(ImVec2((float) posX, (float) posY));
    ImGui::SetWindowSize(ImVec2((float) width, (float) height));
    ImGui::Text("Scene");
    ImGui::BeginChild("Scene", ImVec2((float) width - 20, (float) GLFWHelper::getScreenHeight() / 3), true,
                      ImGuiWindowFlags_HorizontalScrollbar);
    int i = 0;
    for (auto &parent: PabloRenderer::getInstance()->getScene()->root->getChildren()) {
        for (auto &child: parent->getChildren()) {
            if (ImGui::Selectable(child->getRenderable()->name.c_str(), selectedSceneNode == i)) {
                selectedSceneNode = i;
                child->isSelected = true;
                MaterialUI::material = child->getRenderable()->getObjectMaterial();
                SceneNodeUI::sceneNode = child.get();
            } else
                child->isSelected = false;
            i++;
        }
    }
    ImGui::EndChild();

    if(ImGui::Button("Add new")){
        showRendererCreation = true;
    }
    ImGui::NewLine();

;
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
        ImGui::EndTabBar();
    }


    ImGui::End();

    if(showRendererCreation){
        RenderableCreationUI::display();
    }

}
