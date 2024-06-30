//
// Created by wpsimon09 on 22/04/24.
//

#include "FileWindowUI.h"
#include "Renderer/UI/Components/RenderableCreateationUI/RenderableCreationUI.h"

std::string FileWindowUI::display(bool getDirectory ,int widht, int heigh) {
    std::string filePathName;
    std::string directory;
    if (ImGui::Button(getDirectory?"Choose a directory" : "Choose a file")) {
        IGFD::FileDialogConfig config;
        config.path = ".";
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", getDirectory?"Choose a directory" : "Choose a model file", getDirectory ? nullptr :supportedFiles.c_str(), config);
    }
    // display
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            //ImGui::SetNextWindowFocus();

            ImGui::SetNextWindowFocus();
            RenderableCreationUI::hasFocus = true;
            //ImGui::SetNextWindowSize(ImVec2((float)widht,(float) heigh));
            if(getDirectory){
                directory = ImGuiFileDialog::Instance()->GetCurrentPath();
                RenderableBuilder::textureDirectory = directory;
            }
            else{
                filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                RenderableBuilder::modelOath = filePathName;
            }
        }
        // close
        ImGuiFileDialog::Instance()->Close();
        if(getDirectory){
            return directory;
        }else
            return filePathName;

    }
    return "";
}
