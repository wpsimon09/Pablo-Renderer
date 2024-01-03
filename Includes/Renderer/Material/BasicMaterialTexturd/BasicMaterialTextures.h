//
// Created by wpsimon09 on 03/01/24.
//

#ifndef PABLO_RENDERER_BASICMATERIALTEXTURES_H
#define PABLO_RENDERER_BASICMATERIALTEXTURES_H

#include "Renderer/Material/Material.h"
#include "Renderer/Utils/Texture/Texture2D.h"

class BasicMaterialTextures: public  Material{
public:
    BasicMaterialTextures(Shader *shader);
    Texture2D materialTextured
};


#endif //PABLO_RENDERER_BASICMATERIALTEXTURES_H
