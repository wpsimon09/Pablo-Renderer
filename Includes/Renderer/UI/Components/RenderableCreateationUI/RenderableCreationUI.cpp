//
// Created by wpsimon09 on 21/04/24.
//

#include "RenderableCreationUI.h"
#include "Renderer/PabloRenderer.h"
#include "FIleWindowUI/FileWindowUI.h"
#include "Renderer/UI/Components/SceneMenu/SceneMenu.h"



void RenderableCreationUI::display() {
    //ImGui::SetNextWindowFocus();

    ImGui::Begin("Add renderable", nullptr);

    hasFocus = ImGui::IsWindowFocused();


    ImGui::SetWindowSize(ImVec2(400, 400));

    ImGui::InputText("Name",RenderableBuilder::text, 32);

    ImGui::NewLine();
    ImGui::Text("Select properties of material");
    if(ImGui::BeginCombo("Geometry", geometry[RenderableBuilder::selectedGeometry].c_str())){
        for(int i = 0; i<4; i++){
            if(ImGui::Selectable(geometry[i].c_str(), RenderableBuilder::selectedGeometry==i)){
                RenderableBuilder::selectedGeometry= (GEOMETRY)i;
            }
        }
        ImGui::EndCombo();
    }
    if(RenderableBuilder::selectedGeometry == MODEL){
        // button that opens the dialog window is inside the class
        FileWindowUI::display();
        ImGui::Text("Selected model path:");
        ImGui::Text(RenderableBuilder::modelOath.c_str());
    }

    if(RenderableBuilder::selectedGeometry == MODEL){
        ImGui::Checkbox("Keep model material", &RenderableBuilder::keepModelMaterial);
    }

    ImGui::NewLine();

    //display only if the material is selectable
    if(!RenderableBuilder::keepModelMaterial || RenderableBuilder::selectedGeometry != MODEL) {
        ImGui::Text("Select material");
        if(ImGui::BeginCombo("Material", material[RenderableBuilder::selectedMateial].c_str())){
            for(int i = 0; i<2; i++){
                if(ImGui::Selectable(material[i].c_str(), RenderableBuilder::selectedMateial==i)){
                    RenderableBuilder::selectedMateial= (MATERIAL)i;
                }
            }

            ImGui::EndCombo();
        }

        if(RenderableBuilder::selectedMateial == COLOR){
            ImGui::ColorPicker3("Material color", &RenderableBuilder::color.x, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoTooltip | ImGuiColorEditFlags_NoInputs);
        }
        else if (RenderableBuilder::selectedMateial == TEXTURE){
            FileWindowUI::display(true);
            ImGui::Text("Selected texture directory:");
            ImGui::Text(RenderableBuilder::textureDirectory.c_str());
        }
    }


    ImGui::NewLine();
    ImGui::Text("Additional properties");

    ImGui::BeginChild("Other properties");
        ImGui::Checkbox("Casts shadow", &RenderableBuilder::castsShadow);
        ImGui::SameLine();
        ImGui::Checkbox("Supports AreaLight", &RenderableBuilder::supportsAreaLight);
        ImGui::NewLine();
        if(ImGui::Button("Add")){
            auto createdSceneNode = RenderableBuilder::buildRenderable();
            if(createdSceneNode != nullptr){
                PabloRenderer::getInstance()->getScene()->add(std::move(createdSceneNode));
                SceneMenu::showRendererCreation = false;
            }
            else{
                ImGui::Text("Failed to load renderable please change parameters and try again");
            }
        }
        ImGui::SameLine();
    if(ImGui::Button("Cancel")){
            SceneMenu::showRendererCreation = false;
    }
    ImGui::EndChild();


    //ImGui::InputText("Material properties", name, 400);

    ImGui::End();
}

