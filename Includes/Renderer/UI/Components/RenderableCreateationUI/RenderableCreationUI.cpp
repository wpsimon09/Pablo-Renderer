//
// Created by wpsimon09 on 21/04/24.
//

#include "RenderableCreationUI.h"
#include "Renderer/PabloRenderer.h"
#include "FIleWindowUI/FileWindowUI.h"


void RenderableCreationUI::display() {
    //ImGui::SetNextWindowFocus();

    ImGui::Begin("Add renderable", nullptr);

    ImGui::SetWindowSize(ImVec2(400, 400));

    ImGui::NewLine();
    ImGui::Text("Select properties of material");
    if(ImGui::BeginCombo("Geometry", geometry[selectedGeometry].c_str())){
        for(int i = 0; i<4; i++){
            if(ImGui::Selectable(geometry[i].c_str(), selectedGeometry==i)){
                selectedGeometry= (GEOMETRY)i;
            }
        }
        ImGui::EndCombo();
    }
    if(selectedGeometry == MODEL){
        modelOath = FileWindowUI::display();
    }

    ImGui::NewLine();
    ImGui::Text("Select material");
    if(ImGui::BeginCombo("Material", material[selectedMateial].c_str())){
        for(int i = 0; i<2; i++){
            if(ImGui::Selectable(material[i].c_str(), selectedMateial==i)){
                selectedMateial= (MATERIAL)i;
            }
        }

        ImGui::EndCombo();
    }

    if(selectedMateial == COLOR){
        ImGui::ColorPicker3("Material color", &color.x);
    }
    else if (selectedMateial == TEXTURE){
        directory = FileWindowUI::display(true);
    }

    ImGui::NewLine();
    ImGui::Text("Additional properties");

    ImGui::BeginChild("Other properties");
        ImGui::Checkbox("Casts shadow", &castsShadow);
        ImGui::SameLine();
        ImGui::Checkbox("Supports IBL", &supportsIBL);
    ImGui::EndChild();

    ImGui::NewLine();

    ImGui::InputText("default",text, 32);
    //ImGui::InputText("Material properties", name, 400);

    ImGui::End();
}

