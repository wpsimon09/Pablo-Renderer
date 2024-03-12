//
// Created by wpsimon09 on 15/02/24.
//

#include "IBLPipeLine.h"

IBLPipeLine::IBLPipeLine(const char *path) {
    this->inputHDRI = std::make_unique<TextureHDRi>(path);

    this->hdrToCubeMap = std::make_unique<HDRToCubeMap>();
    this->hdrToIrradiance = std::make_unique<Irradiance>();
    this->hdrToPrefilterMap = std::make_unique<PrefilterMap>();
    this->brdfStage = std::make_shared<BRDF>();

}

void IBLPipeLine::generateIBLTextures() {
    //----------------------
    // CONFIGURE HRI TEXTURE
    //----------------------
    this->inputHDRI->setSamplerID(0);

    //-----------------------
    // CREATE ENVIRONMENT MAP
    //-----------------------
    this->hdrToCubeMap->execute(*this->inputHDRI);
    this->envMap = std::move(this->hdrToCubeMap->result);
    this->envMap->setSamplerID(7);

    //----------------------
    // CREATE IRRADIANCE MAP
    //----------------------
    this->hdrToIrradiance->execute(*this->envMap);
    this->iblTextures.push_back(std::make_shared<PBRMaterial<TextureBase>>(std::move(this->hdrToIrradiance->result), "irradianceMap"));

    //---------------------
    // CREATE PREFILTER MAP
    //---------------------
    this->hdrToPrefilterMap->execute(*this->envMap);
    this->iblTextures.push_back(std::make_shared<PBRMaterial<TextureBase>>(std::move(this->hdrToPrefilterMap->result), "prefilterMap"));

    //------------------------
    // CREATE BRDF LUT TEXTURE
    //------------------------
    this->brdfStage->execute();
    this->iblTextures.push_back(std::make_shared<PBRMaterial<TextureBase>>(std::move(this->brdfStage->result), "BRDFtexture"));
}

void IBLPipeLine::configureShader(std::shared_ptr<Shader> shader, int maximalSamplerCount) {
    int i = maximalSamplerCount+1;
    for (auto& iblTexture: this->iblTextures) {
        ShaderHelper::setTextureToShader(shader,*iblTexture->type, iblTexture->shaderName, i);
        i++;
    }
}
