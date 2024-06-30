//
// Created by wpsimon09 on 30/06/24.
//

#ifndef PBRTEXTUREDMATERIALUI_H
#define PBRTEXTUREDMATERIALUI_H
#include <memory>

#include "Renderer/Material/Material.h"
#include "imgui.h"

class PBRTexturedMaterialUI {
private:
    static inline std::shared_ptr<PBRMaterial<Texture2D>> selectedMaterial;
public:
    static inline bool canOpenChangeUI = false;
    static void display(std::vector<std::shared_ptr<PBRMaterial<Texture2D>>> materialTextures);
};



#endif //PBRTEXTUREDMATERIALUI_H
