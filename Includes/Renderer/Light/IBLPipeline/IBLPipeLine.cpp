//
// Created by wpsimon09 on 15/02/24.
//

#include "IBLPipeLine.h"

IBLPipeLine::IBLPipeLine(const char *path) {
    this->inputHDRI = std::make_unique<TextureHDRi>(path);

    this->hdrToCubeMap = std::make_unique<HDRToCubeMap>();
    this->hdrToIrradiance = std::make_unique<Irradiance>();
    this->hdrToPrefilterMap = std::make_shared<PrefilterMap>();

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
    this->irradianceMap = std::move(this->hdrToIrradiance->result);

    //---------------------
    // CREATE PREFILTER MAP
    //---------------------
    this->hdrToPrefilterMap->execute(*this->envMap);
    this->prefilterMap = std::move(this->hdrToPrefilterMap->result);
}
