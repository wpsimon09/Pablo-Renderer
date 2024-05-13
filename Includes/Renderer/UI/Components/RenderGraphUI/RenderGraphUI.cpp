//
// Created by wpsimon09 on 13/05/24.
//

#include "RenderGraphUI.h"
#include "Renderer/PabloRenderer.h"

void RenderGraphUI::display(int posX, int posY, int width, int height) {
    RenderGraphUI::posX = posX;
    RenderGraphUI::poxY = posY;
    RenderGraphUI::width = width;
    RenderGraphUI::height = height;

    auto renderGraph = PabloRenderer::getInstance()->getRenderGraph().getRenderPasses();

    for(auto &renderPass: renderGraph){
        if(ImGui::TreeNode(renderPass.get().getName().c_str())){

            ImGui::TreePop();
        }
    }
}
