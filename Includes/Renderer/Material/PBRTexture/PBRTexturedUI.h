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
                ImGui::Text(texture->shaderName.c_str());
                ImVec2 imageSize((float) texture->type->texWidth / 30, (float) texture->type->texHeight / 30);
                ImGui::SameLine(imageSize.x + 20);
                    ImGui::BeginChild(texture->shaderName.c_str(), imageSize);
                    ImGui::GetWindowDrawList()->AddImage(

                            reinterpret_cast<ImTextureID>(texture->type->ID),
                            ImGui::GetCursorScreenPos(), // Use cursor screen position as top-left corner
                            ImVec2(ImGui::GetCursorScreenPos().x + imageSize.x ,
                                   ImGui::GetCursorScreenPos().y + imageSize.y ), // Use bottom-right corner
                            ImVec2(0, 1),
                            ImVec2(1, 0)
                    );
                    ImGui::EndChild();
            }
        }
}

#endif //PABLO_RENDERER_PBRTEXTUREDUI_H
