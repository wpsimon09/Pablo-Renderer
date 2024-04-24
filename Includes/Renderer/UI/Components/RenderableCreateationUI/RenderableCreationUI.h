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
    inline static GEOMETRY selectedGeometry = CUBE;
    inline static MATERIAL selectedMateial = TEXTURE;

    inline static std::string geometry [] = {
            "CUBE", "SPHERE", "PLANE", "MODEL"
    };

    inline static  std::string material [] = {
            "TEXTURE", "COLOR"
    };

    inline static std::string modelOath;

    inline static glm::vec3 color;
    inline static std::string directory;
    inline static bool castsShadow;
    inline static bool supportsIBL;
    inline static bool keepModelMaterial = false;
    inline static char text[32] = "";
public:
    static void display();
};


#endif //PABLO_RENDERER_RENDERABLECREATIONUI_H
