//
// Created by wpsimon09 on 15/02/24.
//

#include "Irradiance.h"


Irradiance::Irradiance():BaseStage() {
    this->shader = std::make_shared<Shader>("VertexShader/PBR/HDRtoCubeMapVertex.glsl", "FragmentShader/PBR/EnviromentToIrradianceFragment.glsl", "Irradiance map shader");
    this->shaderName = "irradianceMap";
}

void Irradiance::execute(TextureBase input) {
    this->frameBufferCube = std::make_unique<FrameBufferCube>(32,32, this->shader);
    this->result = this->frameBufferCube->renderToSelf(input);
    this->frameBufferCube.reset();
}

