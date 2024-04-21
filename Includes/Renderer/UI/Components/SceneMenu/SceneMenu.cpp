//
// Created by wpsimon09 on 19/04/24.
//

#include "SceneMenu.h"
#include "Renderer/UI/Components/MaterialUI/MaterialUI.h"
#include "Renderer/UI/Components/SceneNodeUI/SceneNodeUI.h"

void SceneMenu::display(int posX, int posY, int width, int height) {
    Component::posX = posX;
    Component::poxY = posY;
    Component::width = width;
    Component::height = height;

    ImGui::Begin("Tools", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::SetWindowPos(ImVec2((float) posX, (float) posY));
    ImGui::SetWindowSize(ImVec2((float) width, (float) GLFWHelper::getScreenHeight(200)));
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
    if (ImGui::IsItemClicked()){
        selectedSceneNode = -1;
        MaterialUI::material = nullptr;
    }

    ImGui::BeginChild("Light section", ImVec2(width - 20, 0), true, ImGuiWindowFlags_HorizontalScrollbar);

    MaterialUI::display(width-20,0, width);


    SceneNodeUI::display();

    if (ImGui::TreeNode("Debug texture")) {
        ImVec2 imageSize((float) debugTexture->texWidth, (float) debugTexture->texHeight);
        ImGui::GetWindowDrawList()->AddImage(

                (void *) debugTexture->ID,
                ImGui::GetCursorScreenPos(), // Use cursor screen position as top-left corner
                ImVec2(ImGui::GetCursorScreenPos().x + imageSize.x / 4,
                       ImGui::GetCursorScreenPos().y + imageSize.y / 4), // Use bottom-right corner
                ImVec2(0, 1),
                ImVec2(1, 0)
        );
        ImGui::TreePop();
    };
    GLFWHelper::getInstance()->getScene()->light->renderUi();
    ImGui::EndChild();

    ImGui::End();
}
