//
// Created by wpsimon09 on 22/04/24.
//

#ifndef PABLO_RENDERER_FILEWINDOWUI_H
#define PABLO_RENDERER_FILEWINDOWUI_H

#include "iostream"
#include "imgui.h"
#include "ImGuiFileDialog/ImGuiFileDialog.h"

class FileWindowUI {
public:
    static inline std::string supportedFiles = ".gltf,.obj,.glb,.fbx";
    static std::string display(bool getDirectory = false, int widht = 600, int heigh = 600);
};


#endif //PABLO_RENDERER_FILEWINDOWUI_H
