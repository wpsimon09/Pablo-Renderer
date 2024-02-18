//
// Created by wpsimon09 on 15/02/24.
//

#include "HDRToCubeMap.h"

HDRToCubeMap::HDRToCubeMap(): BaseStage(), result(1980, 1980, GL_RGB32F) {
    this->shader = new Shader("VertexShader/PBR/HDRtoCubeMapVertex.glsl", "FragmentShader/PBR/HDRtoCubeMapFragment.glsl", "Cube map shader");
    this->frameBufferCube = new FrameBufferCube(1980, 1980,this->shader,std::move(result));
}

void HDRToCubeMap::execute(TextureBase input) {
    ShaderHelper::setTextureToShader(this->shader, std::move(input), "envMap");
    this->result = this->frameBufferCube->renderToSelf();
    //texture has no sampler probably here
    //delete this->frameBufferCube;
}
