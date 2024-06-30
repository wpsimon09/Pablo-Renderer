//
// Created by wpsimon09 on 26/06/24.
//

#ifndef CHANGESINGLETEXTUREUI_H
#define CHANGESINGLETEXTUREUI_H
#include "Renderer/Material/Material.h"
#include "Renderer/Material/PBRTexture/PBRTextured.h"


class ChangeSingleTextureUI {
private:
    inline static std::shared_ptr<Texture2D> selectedID;
    static void addTextureFromDirectory(MATERIAL_TEXTURE_TYPE textureType);
public:
    inline static std::string newTexturePath = "";
    inline static std::shared_ptr<Texture2D> newTexture = nullptr;
    inline static bool canShow = false;
    static void display(std::shared_ptr<PBRMaterial<Texture2D>> &materialToChange, MATERIAL_TEXTURE_TYPE textureToChange);

};



#endif //CHANGESINGLETEXTUREUI_H
