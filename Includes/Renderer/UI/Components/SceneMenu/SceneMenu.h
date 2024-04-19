//
// Created by wpsimon09 on 19/04/24.
//

#ifndef PABLO_RENDERER_SCENEMENU_H
#define PABLO_RENDERER_SCENEMENU_H

#include "imgui.h"
#include "Renderer/PabloRenderer.h"
#include "Renderer/UI/Components/Component.h"

class SceneMenu:public Component {
public:
    inline static std::shared_ptr<Texture2D> debugTexture;
    static void display(int posX, int posY, int width, int height = 0);
};


#endif //PABLO_RENDERER_SCENEMENU_H
