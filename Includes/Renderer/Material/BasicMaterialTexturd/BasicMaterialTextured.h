//
// Created by wpsimon09 on 03/01/24.
//

#ifndef PABLO_RENDERER_BASICMATERIALTEXTURED_H
#define PABLO_RENDERER_BASICMATERIALTEXTURED_H

#include "Renderer/Material/Material.h"
#include "Renderer/Utils/Texture/Texture2D.h"

class BasicMaterialTextured: public  Material{
public:
    BasicMaterialTextured(Shader *shader, const char* path);
    Texture2D *texture;
};


#endif //PABLO_RENDERER_BASICMATERIALTEXTURED_H
