//
// Created by wpsimon09 on 15/02/24.
//

#include "Irradiance.h"


Irradiance::Irradiance():BaseStage() {
    this->shader = ShaderManager::getShader(SHADER_GENERATE_IRRADIANCE);
    this->shaderName = "irradianceMap";
}

void Irradiance::execute(TextureBase input) {
    if(fistExecution){
        this->frameBufferCube = std::make_unique<FrameBufferCube>(32,32, this->shader);
        this->fistExecution = false;
    }
    this->result = this->frameBufferCube->renderToSelf(input);
}

