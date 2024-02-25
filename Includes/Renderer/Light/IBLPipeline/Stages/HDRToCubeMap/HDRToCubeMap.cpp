//
// Created by wpsimon09 on 15/02/24.
//

#include "HDRToCubeMap.h"

HDRToCubeMap::HDRToCubeMap(): BaseStage() {
    this->shader = std::make_shared<Shader>("VertexShader/PBR/HDRtoCubeMapVertex.glsl", "FragmentShader/PBR/HDRtoCubeMapFragment.glsl", "Cube map shader");
    this->result = std::make_unique<Texture3D>(1980, 1980, GL_RGB32F);
}

void HDRToCubeMap::execute(TextureBase input) {
    this->frameBufferCube = std::make_unique<FrameBufferCube>(1980, 1980,this->shader);
    this->result = this->frameBufferCube->renderToSelf(input);
    //texture has no sampler probably here
    //delete this->frameBufferCube;
}
