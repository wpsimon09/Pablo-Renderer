//
// Created by wpsimon09 on 15/02/24.
//

#include "PrefilterMap.h"

PrefilterMap::PrefilterMap():BaseStage() {
    this->shader = ShaderManager::getShader(SHADER_GENERATE_PREFILTER);
    this->shaderName = "prefilterMap";
}

void PrefilterMap::execute(TextureBase input) {
    unsigned int maxMipMapLevels = 6;
    if(fistExecution){
        this->frameBufferCube = std::make_unique<FrameBufferCube>(512,512, this->shader, maxMipMapLevels);
        this->frameBufferCube->colorAttachmentCube->changeFilteringMethod(GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);
        this->fistExecution = false;
    }

    for (int mip = 0; mip < maxMipMapLevels; ++mip) {
        unsigned int mipW =  static_cast<unsigned int>(512 * std::pow(0.5, mip));
        unsigned int mipH =  static_cast<unsigned int>(512 * std::pow(0.5, mip));

        this->frameBufferCube->updateDimetions(mipW, mipH);
        
        float rougness = (float)mip/(float)(maxMipMapLevels-1);
        shader->setFloat("rougness", rougness);

        this->frameBufferCube->renderToSelf(input, mip);
    }
    this->result = frameBufferCube->colorAttachmentCube;
}
