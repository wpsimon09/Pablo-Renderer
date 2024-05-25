//
// Created by wpsimon09 on 15/02/24.
//

#include "HDRToCubeMap.h"

HDRToCubeMap::HDRToCubeMap(): BaseStage() {
    this->shader = ShaderManager::getShader(SHADER_HDR_2_CUBE_MAP);
    this->shaderName = "envMap";
}

void HDRToCubeMap::execute(TextureBase input) {
    if(fistExecution){
        this->frameBufferCube = std::make_unique<FrameBufferCube>(1980, 1980,this->shader);
    }
    this->result = this->frameBufferCube->renderToSelf(input);
}
