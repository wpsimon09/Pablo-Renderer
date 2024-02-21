//
// Created by wpsimon09 on 15/02/24.
//

#include "HDRToCubeMap.h"

HDRToCubeMap::HDRToCubeMap(): BaseStage() {
    this->shader = std::make_unique<Shader>("VertexShader/PBR/HDRtoCubeMapVertex.glsl", "FragmentShader/PBR/HDRtoCubeMapFragment.glsl", "Cube map shader");
    this->result = std::make_unique<Texture3D>(1980, 1980, GL_RGB32F);
    this->frameBufferCube = std::make_unique<FrameBufferCube>(1980, 1980,std::move(this->shader),std::move(result));
}

void HDRToCubeMap::execute(TextureBase input) {
    ShaderHelper::setTextureToShader(std::move(this->shader), std::move(input), "envMap");
    this->result = this->frameBufferCube->renderToSelf();
    //texture has no sampler probably here
    //delete this->frameBufferCube;
}
