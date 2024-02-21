//
// Created by wpsimon09 on 15/02/24.
//

#include "IBLPipeLine.h"

IBLPipeLine::IBLPipeLine(const char *path) {
    this->hdrToCubeMap = std::make_unique<HDRToCubeMap>();
    this->hdriTexture = std::make_unique<TextureHDRi>(path);
}

void IBLPipeLine::generateIBLTextures() {
    this->hdriTexture->setSamplerID(0);
    this->hdrToCubeMap->execute(*this->hdriTexture);
    this->envMap = std::move(hdrToCubeMap->result);
}
