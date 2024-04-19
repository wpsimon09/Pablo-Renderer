//
// Created by wpsimon09 on 19/04/24.
//

#ifndef PABLO_RENDERER_BOTTOMMENU_H
#define PABLO_RENDERER_BOTTOMMENU_H

#include "imgui.h"
#include "Renderer/UI/Components/Component.h"

class BottomMenu:public Component {
public:
    static inline ImGuiIO *imGuiIo;
    static void display(int posX, int posY, int width, int height);
};


#endif //PABLO_RENDERER_BOTTOMMENU_H
