//
// Created by wpsimon09 on 15/02/24.
//

#include "IBLPipeLine.h"

IBLPipeLine::IBLPipeLine(const char *path): hdriTexture(path) {
    this->hdrToCubeMap = new HDRToCubeMap();
}

void IBLPipeLine::generateIBLTextures() {
    this->hdriTexture.setSamplerID(0);
    this->hdrToCubeMap->execute(std::move(this->hdriTexture));
    this->envMap = std::move(hdrToCubeMap->result);
}
