//
// Created by wpsimon09 on 03/01/24.
//

#ifndef PABLO_RENDERER_BASICMATERIALTEXTURED_H
#define PABLO_RENDERER_BASICMATERIALTEXTURED_H

#include "Renderer/Material/Material.h"
#include "Renderer/Utils/Texture/Texture2D.h"
struct TextureUniform{
    std::string shaderName;
    Texture2D *texture2D;

    TextureUniform(std::string shaderName, Texture2D *texture){
        this->shaderName = shaderName;
        this->texture2D = texture;
    }
};

class BasicMaterialTextured: public  Material{
public:
    BasicMaterialTextured(Shader *shader, const char* path, std::string shaderName = "FragmentColor");

    BasicMaterialTextured(Shader* shader, Texture2D* texture2D, std::string shaderName = "FragmentColor");
    void configureShader() override;

    TextureUniform *texture;
};

#endif //PABLO_RENDERER_BASICMATERIALTEXTURED_H
