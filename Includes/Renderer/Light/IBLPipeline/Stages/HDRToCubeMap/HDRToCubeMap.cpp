//
// Created by wpsimon09 on 15/02/24.
//

#include "HDRToCubeMap.h"

HDRToCubeMap::HDRToCubeMap(): BaseStage() {
    this->shader = new Shader("VertexShader/PBR/HDRtoCubeMapVertex.glsl", "FragmentShader/PBR/HDRtoCubeMapFragment.glsl", "Cube map shader");
    this->result = std::make_unique<Texture3D>(1980, 1980, GL_RGB32F);
    this->frameBufferCube = new FrameBufferCube(1980, 1980,this->shader,std::move(result));
}

void HDRToCubeMap::execute(std::unique_ptr<TextureBase> input) {
    ShaderHelper::setTextureToShader(this->shader, std::move(input), "envMap");
    this->result = this->frameBufferCube->renderToSelf();
    //texture has no sampler probably here
    //delete this->frameBufferCube;
}
