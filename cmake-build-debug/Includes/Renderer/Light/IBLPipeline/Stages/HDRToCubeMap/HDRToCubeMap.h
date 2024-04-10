//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_HDRTOCUBEMAP_H
#define PABLO_RENDERER_HDRTOCUBEMAP_H

#include "Renderer/Light/IBLPipeline/Stages/BaseStage.h"
#include "Renderer/Utils/Texture/TextureHDR/TextureHDRi.h"

/***
 * Converts equirectangular map to the Cube Map
 */
class HDRToCubeMap:public BaseStage {
public:
    HDRToCubeMap();
    void execute(TextureBase input) override;
protected:
    std::unique_ptr<FrameBufferCube> frameBufferCube;
};


#endif //PABLO_RENDERER_HDRTOCUBEMAP_H
