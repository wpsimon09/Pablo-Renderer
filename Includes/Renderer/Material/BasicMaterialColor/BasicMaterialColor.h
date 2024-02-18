//
// Created by wpsimon09 on 14/02/24.
//

#ifndef PABLO_RENDERER_BASICMATERIALCOLOR_H
#define PABLO_RENDERER_BASICMATERIALCOLOR_H

#include <utility>

#include "iostream"
#include "Renderer/Material/Material.h"

struct ColorUnifrom{
    std::string shaderName;
    glm::vec3 value;
    ColorUnifrom(std::string shaderName, glm::vec3 color){
        this->shaderName = std::move(shaderName);
        this->value = color;
    }
};

class BasicMaterialColor:public Material {
public:
    BasicMaterialColor(std::unique_ptr<Shader> shader, glm::vec3 color = glm::vec3(1.0), std::string shaderName="color");
    void configureShader() override;
private:
    std::unique_ptr<ColorUnifrom> color;
};


#endif //PABLO_RENDERER_BASICMATERIALCOLOR_H
