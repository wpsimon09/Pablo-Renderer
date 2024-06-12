//
// Created by wpsimon09 on 09/06/24.
//

#ifndef PABLO_RENDERER_CHANGEMATERIALUI_H
#define PABLO_RENDERER_CHANGEMATERIALUI_H

#include "imgui.h"
#include "Renderer/Enums/UIBuilderEnums.h"
#include "string"
#include "memory"
#include "Renderer/Renderable/Renderable.h"
#include "Renderer/UI/Components/MaterialUI/MaterialUI.h"

class ChangeMaterialUI{
public:
    static void display(Renderable *renderable);
private:
    static inline MATERIAL selectedMaterial;
    inline static  std::string material [] = {
            "PBR_TEXTURE_MAPS", "COLOR"
    };
    inline static std::string texturesDirectory;
    inline static glm::vec3 color = glm::vec3(0.0f, 0.0F, 0.0F);
};


#endif //PABLO_RENDERER_CHANGEMATERIALUI_H
