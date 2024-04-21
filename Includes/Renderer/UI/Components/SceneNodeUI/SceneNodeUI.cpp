//
// Created by wpsimon09 on 20/04/24.
//

#include "SceneNodeUI.h"
#include "Renderer/UI/Components/MaterialUI/MaterialUI.h"

void SceneNodeUI::display() {

    if(sceneNode!= nullptr){
        if(ImGui::TreeNodeEx(sceneNode->getRenderable()->name.c_str())){
            if(ImGui::TreeNodeEx("Position")){

                ImGui::SliderFloat("X", &sceneNode->transformation->getPosition_UI().x, -10.0f, 10.0f);
                ImGui::SliderFloat("Y", &sceneNode->transformation->getPosition_UI().y, -10.0f, 10.0f);
                ImGui::SliderFloat("Z", &sceneNode->transformation->getPosition_UI().z, -10.0f, 10.0f);

                if(ImGui::Button("Reset")){
                    sceneNode->transformation->setPosition(sceneNode->getInitialPosition());
                }

                ImGui::TreePop();
            }

            if(ImGui::TreeNodeEx("Rotation")){

                ImGui::SliderFloat("X", &sceneNode->transformation->getRotation_UI().x, 0.0f, 360.0f);
                ImGui::SliderFloat("Y", &sceneNode->transformation->getRotation_UI().y, 0.0f, 360.0f);
                ImGui::SliderFloat("Z", &sceneNode->transformation->getRotation_UI().z, 0.0f, 360.0f);

                if(ImGui::Button("Reset")){
                    sceneNode->transformation->setRotations(sceneNode->getInitialRotation());
                }

                ImGui::TreePop();
            }

            if(ImGui::TreeNodeEx("Scale")){

                ImGui::SliderFloat("X", &sceneNode->transformation->getScale_UI().x,0.0f, 100.0f);
                ImGui::SliderFloat("Y", &sceneNode->transformation->getScale_UI().y,0.0f, 100.0f);
                ImGui::SliderFloat("Z", &sceneNode->transformation->getScale_UI().z,0.0f, 100.0f);


                if(ImGui::Button("Reset")){
                    sceneNode->transformation->setScale(sceneNode->getInitialScale());
                }

                ImGui::TreePop();
            }

            if(ImGui::Button("Reset all")){
                sceneNode->transformation->setPosition(sceneNode->getInitialPosition());
                sceneNode->transformation->setRotations(sceneNode->getInitialRotation());
                sceneNode->transformation->setScale(sceneNode->getInitialScale());
            }
            ImGui::SameLine();
            ImGui::Checkbox("Is visible", &sceneNode->getVisibility());
            ImGui::TreePop();
        }
    }
}

