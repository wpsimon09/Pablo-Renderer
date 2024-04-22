//
// Created by wpsimon09 on 22/04/24.
//

#include "FileWindowUI.h"

std::string FileWindowUI::display(bool getDirectory ,int widht, int heigh) {
    std::string filePathName;
    std::string directory;
    if (ImGui::Button(getDirectory?"Choose a directory" : "Choose a model file")) {
        IGFD::FileDialogConfig config;
        config.path = ".";
        ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", getDirectory?"Choose a directory" : "Choose a model file", getDirectory ? nullptr :".gltf,.obj,.glb", config);
    }
    // display
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
        if (ImGuiFileDialog::Instance()->IsOk()) {
            //ImGui::SetNextWindowFocus();
            ImGui::SetNextWindowFocus();
            ImGui::SetNextWindowSize(ImVec2((float)widht,(float) heigh));
            filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            directory = ImGuiFileDialog::Instance()->GetCurrentPath();
        }
        // close
        ImGuiFileDialog::Instance()->Close();

        return getDirectory ? directory : filePathName;
    }
    return "";
}
