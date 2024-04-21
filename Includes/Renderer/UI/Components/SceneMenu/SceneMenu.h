//
// Created by wpsimon09 on 19/04/24.
//

#ifndef PABLO_RENDERER_SCENEMENU_H
#define PABLO_RENDERER_SCENEMENU_H

#include "imgui.h"
#include "Renderer/PabloRenderer.h"
#include "Renderer/UI/Components/Component.h"

class SceneMenu:public Component {
private:
    /***
     * Selected scene node Index
     * @def -1 means nothing is selected
     */
    inline static int selectedSceneNode = -1;

    inline static bool showLight = false;
    inline static bool showTransformation = false;
public:
    static void display(int posX, int posY, int width, int height = 0);
};


#endif //PABLO_RENDERER_SCENEMENU_H
