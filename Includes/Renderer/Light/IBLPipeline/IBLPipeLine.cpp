//
// Created by wpsimon09 on 15/02/24.
//

#include "IBLPipeLine.h"

IBLPipeLine::IBLPipeLine(const char *path) {
    this->inputHDRI = std::make_unique<TextureHDRi>(path);

    stages.push_back(std::make_unique<HDRToCubeMap>());
    stages.push_back(std::make_unique<Irradiance>());
    stages.push_back(std::make_unique<PrefilterMap>());
    stages.push_back(std::make_unique<BRDF>());
}

void IBLPipeLine::generateIBLTextures() {
    //----------------------
    // CONFIGURE HRI TEXTURE
    //----------------------
    this->inputHDRI->setSamplerID(0);

    bool firstIteration = true;
    for(auto &stage: stages){
        // for the first iteration HDR map should be input for the rest of the IBL stages
        // Environment map should be the input which is always stored as first IBL texture
        stage->execute(firstIteration ? *this->inputHDRI : *iblTextures[0]->type);
        this->iblTextures.push_back(std::make_shared<PBRMaterial<TextureBase>>(std::move(stage->result), stage->shaderName));
        firstIteration = false;
    }

    this->envMap = this->iblTextures[0]->type;
    this->envMap->setSamplerID(7);
}

void IBLPipeLine::configureShader(std::shared_ptr<Shader> shader, int maximalSamplerCount) {
    int i = maximalSamplerCount+1;
    for (auto& iblTexture: this->iblTextures) {
        ShaderHelper::setTextureToShader(shader,*iblTexture->type, iblTexture->shaderName, i);
        i++;
    }
}
