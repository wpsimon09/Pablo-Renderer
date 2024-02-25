//
// Created by wpsimon09 on 15/02/24.
//

#include "IBLPipeLine.h"

IBLPipeLine::IBLPipeLine(const char *path) {
    this->hdrToCubeMap = std::make_unique<HDRToCubeMap>();
    this->hdrToIrradiance = std::make_unique<Irradiance>();
    this->inputHDRI = std::make_unique<TextureHDRi>(path);

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
}
