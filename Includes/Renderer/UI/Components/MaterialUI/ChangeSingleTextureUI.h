//
// Created by wpsimon09 on 26/06/24.
//

#ifndef CHANGESINGLETEXTUREUI_H
#define CHANGESINGLETEXTUREUI_H
#include "Renderer/Material/Material.h"
#include "Renderer/Material/PBRTexture/PBRTextured.h"


class ChangeSingleTextureUI {
public:
    static void display(std::shared_ptr<PBRTextured> materialToChange, MATERIAL_TEXTURE_TYPE textureToChange);

};



#endif //CHANGESINGLETEXTUREUI_H
