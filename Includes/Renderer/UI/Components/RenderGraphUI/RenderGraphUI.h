//
// Created by wpsimon09 on 13/05/24.
//

#ifndef PABLO_RENDERER_RENDERGRAPHUI_H
#define PABLO_RENDERER_RENDERGRAPHUI_H

#include "Renderer/UI/Components/Component.h"
#include "imgui.h"


class RenderGraphUI: public Component {
public:
    static void display(int posX, int posY, int width, int height);
};

#endif //PABLO_RENDERER_RENDERGRAPHUI_H
