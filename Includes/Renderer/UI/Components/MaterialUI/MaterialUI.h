//
// Created by wpsimon09 on 20/04/24.
//

#ifndef PABLO_RENDERER_MATERIALUI_H
#define PABLO_RENDERER_MATERIALUI_H

#include "Renderer/UI/Components/Component.h"
#include "Renderer/Material/Material.h"
#include "imgui.h"

class MaterialUI:public Component {
    inline static std::shared_ptr<Material> debugTexture;
    static void display(int posX, int posY, int width, int height = 0);

};


#endif //PABLO_RENDERER_MATERIALUI_H
