//
// Created by wpsimon09 on 16/02/24.
//

#ifndef PABLO_RENDERER_SKYBOXMATERIAL_H
#define PABLO_RENDERER_SKYBOXMATERIAL_H

#include "Renderer/Material/Material.h"
#include "Renderer/Utils/Texture/Texture3D/Texture3D.h"

struct CubeMapUnifrom{
    Texture3D cubeMap;
    std::string shaderName;

    CubeMapUnifrom(Texture3D cubeMapTexture, std::string shaderName){
        this->cubeMap = std::move(cubeMapTexture);
        this->shaderName = std::move(shaderName);
    }
};

class SkyBoxMaterial: public Material {
public:
    SkyBoxMaterial(Shader* shader, Texture3D skyBox, std::string shaderName);

    void configureShader() override;

private:
    CubeMapUnifrom* cubeMapUnifrom;
};


#endif //PABLO_RENDERER_SKYBOXMATERIAL_H
