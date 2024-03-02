//
// Created by wpsimon09 on 15/02/24.
//

#include "BRDF.h"

BRDF::BRDF() {
    this->shader = std::make_shared<Shader>("VertexShader/PBR/LutTextureVertex.glsl", "FragmentShader/PBR/BRDFLutFragment.glsl", "LUT_Textue map");
}

void BRDF::execute() {
    auto colorAttachemnt = std::make_unique<Texture2D>(512,512, GL_RG16F);
    colorAttachemnt->setUnpaceAlligment(6);
    this->frameBuffer = std::make_unique<FrameBuffer>(512,512, this->shader,std::move(colorAttachemnt));
    this->frameBuffer->drawInsideSelf();
    this->result = std::move(frameBuffer->getRenderedResult());
    //frameBuffer.reset();
}
