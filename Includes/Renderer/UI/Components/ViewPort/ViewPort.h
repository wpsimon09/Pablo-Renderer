//
// Created by wpsimon09 on 19/04/24.
//

#ifndef PABLO_RENDERER_VIEWPORT_H
#define PABLO_RENDERER_VIEWPORT_H

#include "imgui.h"
#include "Renderer/PabloRenderer.h"
#include "Renderer/UI/Components/Component.h"
class ViewPort:public Component {
public:
    inline static std::shared_ptr<Texture2D> renderedScene;
    static void display(int posX, int posY, int width, int height);
};


#endif //PABLO_RENDERER_VIEWPORT_H
