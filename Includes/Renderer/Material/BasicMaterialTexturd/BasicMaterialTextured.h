//
// Created by wpsimon09 on 03/01/24.
//

#ifndef PABLO_RENDERER_BASICMATERIALTEXTURED_H
#define PABLO_RENDERER_BASICMATERIALTEXTURED_H

#include "Renderer/Material/Material.h"
#include "Renderer/Utils/Texture/Texture2D/Texture2D.h"
struct TextureUniform{
    std::string shaderName;
    TextureBase texture2D;

    TextureUniform(std::string shaderName, TextureBase texture){
        this->shaderName = shaderName;
        this->texture2D = std::move(texture);
    }
};

class BasicMaterialTextured: public  Material{
public:
    BasicMaterialTextured(std::unique_ptr<Shader> shader, const char* path, std::string shaderName = "FragmentColor");

    BasicMaterialTextured(std::unique_ptr<Shader> shader, TextureBase texture2D, std::string shaderName = "FragmentColor");

    void configureShader() override;

    std::unique_ptr<TextureUniform> texture;
};

#endif //PABLO_RENDERER_BASICMATERIALTEXTURED_H
