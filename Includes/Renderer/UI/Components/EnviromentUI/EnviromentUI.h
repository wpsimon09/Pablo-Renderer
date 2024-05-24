//
// Created by wpsimon09 on 23/05/24.
//

#ifndef PABLO_RENDERER_ENVIROMENTUI_H
#define PABLO_RENDERER_ENVIROMENTUI_H

#include "iostream"
#include "Renderer/UI/Components/Component.h"

class EnviromentUI:public Component {
private:
    static inline std::string hdrTexturePath ="";
public:
    static void display();
};


#endif //PABLO_RENDERER_ENVIROMENTUI_H
