//
// Created by wpsimon09 on 21/04/24.
//

#ifndef PABLO_RENDERER_RENDERABLECREATIONUI_H
#define PABLO_RENDERER_RENDERABLECREATIONUI_H

#include "Renderer/UI/Components/Component.h"
#include "ImGuiFileDialog/ImGuiFileDialog.h"
#include <map>
#include "string"
#include "glm/glm.hpp"
#include "Renderer/Utils/RenderableBuilder/RenderableBuilder.h"

class RenderableCreationUI:public Component {
private:
    inline static std::string geometry [] = {
            "CUBE", "SPHERE", "PLANE", "MODEL"
    };

    inline static  std::string material [] = {
            "PBR_TEXTURE_MAPS", "COLOR"
    };

public:
    static inline bool hasFocus = false;
    static void display();
};


#endif //PABLO_RENDERER_RENDERABLECREATIONUI_H
