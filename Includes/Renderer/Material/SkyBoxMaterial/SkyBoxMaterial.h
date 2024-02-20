//
// Created by wpsimon09 on 16/02/24.
//

#ifndef PABLO_RENDERER_SKYBOXMATERIAL_H
#define PABLO_RENDERER_SKYBOXMATERIAL_H

#include "Renderer/Material/Material.h"
#include "Renderer/Utils/Texture/Texture3D/Texture3D.h"

struct CubeMapUnifrom{
    std::unique_ptr<Texture3D> cubeMap;
    std::string shaderName;

    CubeMapUnifrom(std::unique_ptr<Texture3D> cubeMapTexture, std::string shaderName){
        this->cubeMap = std::move(cubeMapTexture);
        this->shaderName = std::move(shaderName);
    }
};

class SkyBoxMaterial: public Material {
public:
    SkyBoxMaterial(std::unique_ptr<Shader> shader,std::unique_ptr<Texture3D> skyBox, std::string shaderName);

    void configureShader() override;

private:
    CubeMapUnifrom* cubeMapUnifrom;
};


#endif //PABLO_RENDERER_SKYBOXMATERIAL_H
