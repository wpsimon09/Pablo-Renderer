//
// Created by wpsimon09 on 21/04/24.
//

#ifndef PABLO_RENDERER_LIGHTUI_H
#define PABLO_RENDERER_LIGHTUI_H

#include "Renderer/UI/Components/Component.h"
#include "memory"
#include "Renderer/Utils/Texture/Texture2D/Texture2D.h"

class LightUI:public Component {
public:
    inline static std::shared_ptr<Texture2D> debugTexture;
    static void display(int posX, int posY, int width, int height= 0);
};


#endif //PABLO_RENDERER_LIGHTUI_H
