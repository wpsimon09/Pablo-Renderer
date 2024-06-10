//
// Created by wpsimon09 on 20/04/24.
//

#ifndef PABLO_RENDERER_MATERIALUI_H
#define PABLO_RENDERER_MATERIALUI_H

#include "Renderer/UI/Components/Component.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Renderable/Renderable.h"
#include "imgui.h"

class MaterialUI:public Component {
public:
    inline static Renderable* renderable = nullptr;
    static void display(int posX, int posY, int width, int height = 0);
    inline static bool displayChangeMaterialUI = false;
};


#endif //PABLO_RENDERER_MATERIALUI_H
