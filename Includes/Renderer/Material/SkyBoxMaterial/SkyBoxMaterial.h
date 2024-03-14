//
// Created by wpsimon09 on 16/02/24.
//

#ifndef PABLO_RENDERER_SKYBOXMATERIAL_H
#define PABLO_RENDERER_SKYBOXMATERIAL_H

#include "Renderer/Material/Material.h"
#include "Renderer/Utils/Texture/Texture3D/Texture3D.h"

/***
 * Structure representing cube map which is later passed to the shader as a uniform
 */
struct CubeMapUnifrom {
    TextureBase cubeMap;
    std::string shaderName;

    /***
     * Creates the unifrom
     * @param cubeMapTexture cube map texture that will be used as sky-box
     * @param shaderName name of the uniform in the shader
     */
    CubeMapUnifrom(TextureBase cubeMapTexture, std::string shaderName) {
        this->cubeMap = std::move(cubeMapTexture);
        this->shaderName = std::move(shaderName);
    }
};

/**
 * class representing skybox  materials?
 */
class SkyBoxMaterial : public Material {
public:
    SkyBoxMaterial(std::shared_ptr<Shader> shader, TextureBase skyBox, std::string shaderName);
    /**
    * passes all relevant uniform to the shader
    */
    void configureShader() override;

private:
    CubeMapUnifrom *cubeMapUnifrom;
};


#endif //PABLO_RENDERER_SKYBOXMATERIAL_H
