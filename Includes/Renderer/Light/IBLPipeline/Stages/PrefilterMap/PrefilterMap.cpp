//
// Created by wpsimon09 on 15/02/24.
//

#include "PrefilterMap.h"

PrefilterMap::PrefilterMap() {
    this->shader = std::make_shared<Shader>("VertexShader/PBR/HDRtoCubeMapVertex.glsl", "FragmentShader/PBR/PrefilteringHDRFragment.glsl", "Prefiltering cubeData map");
}

void PrefilterMap::execute(TextureBase input) {
    unsigned int maxMipMapLevels = 5;

    this->frameBufferCube = std::make_unique<FrameBufferCube>(128,128, this->shader, maxMipMapLevels);
    this->frameBufferCube->colorAttachmentCube->changeFilteringMethod(GL_LINEAR, GL_LINEAR_MIPMAP_LINEAR);

    for (int mip = 0; mip < maxMipMapLevels; ++mip) {
        unsigned int mipW =  static_cast<unsigned int>(128 * std::pow(0.5, mip));
        unsigned int mipH =  static_cast<unsigned int>(128 * std::pow(0.5, mip));

        this->frameBufferCube->updateDimetions(mipW, mipH);
        
        float rougness = (float)mip/(float)(maxMipMapLevels-1);
        shader->setFloat("rougness", rougness);

        this->frameBufferCube->renderToSelf(input, mip);
    }
    this->result = frameBufferCube->colorAttachmentCube;
}
