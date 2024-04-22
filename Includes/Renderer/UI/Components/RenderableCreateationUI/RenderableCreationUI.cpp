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

    ImGui::Text("Select properties of material");
    ImGui::NewLine();
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

    if(ImGui::BeginCombo("Material", geometry[selectedMateial].c_str())){
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
    ImGui::End();
}

