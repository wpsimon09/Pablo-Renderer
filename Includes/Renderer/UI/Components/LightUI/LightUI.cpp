//
// Created by wpsimon09 on 21/04/24.
//

#include "LightUI.h"
#include "Renderer/PabloRenderer.h"

void LightUI::display(int posX, int posY, int width, int height) {
    ImGui::Text("Light");

    auto lights = PabloRenderer::getInstance()->getScene()->lights.begin();

    while(lights!= PabloRenderer::getInstance()->getScene()->lights.end()){
        lights->second->renderUi();
        lights++;
    }

    //nderer::getInstance()->getScene()->light->renderUi();
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
}
