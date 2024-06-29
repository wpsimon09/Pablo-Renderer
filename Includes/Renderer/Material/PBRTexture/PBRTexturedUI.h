//
// Created by wpsimon09 on 12/06/24.
//

#ifndef PABLO_RENDERER_PBRTEXTUREDUI_H
#define PABLO_RENDERER_PBRTEXTUREDUI_H
#include "imgui.h"
#include "vector"
#include "memory"

inline void DisplayMaterialTexturedUI(std::vector<std::shared_ptr<PBRMaterial<Texture2D>>> textures){
        for (auto &texture: textures) {
            if(texture->type != nullptr && texture != nullptr && texture->type->wasFound){
                ImVec2 imageSize((float) 60, (float) 60);
                ImGui::ImageButton(texture->shaderName.c_str(), reinterpret_cast<ImTextureID>(texture->type->ID), imageSize);
                ImGui::SameLine(imageSize.x + 20);
                ImGui::Text(texture->shaderName.c_str());
            }
        }
}

#endif //PABLO_RENDERER_PBRTEXTUREDUI_H
