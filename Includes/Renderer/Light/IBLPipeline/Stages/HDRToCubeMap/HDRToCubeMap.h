//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_HDRTOCUBEMAP_H
#define PABLO_RENDERER_HDRTOCUBEMAP_H

#include "Renderer/Light/IBLPipeline/Stages/BaseStage.h"
#include "Renderer/Utils/Texture/TextureHDR/TextureHDRi.h"

class HDRToCubeMap:public BaseStage {
public:
    HDRToCubeMap();
    void execute(std::unique_ptr<TextureBase> input) override;
    std::unique_ptr<Texture3D> result;
protected:
    std::unique_ptr<FrameBufferCube> frameBufferCube;
};


#endif //PABLO_RENDERER_HDRTOCUBEMAP_H
