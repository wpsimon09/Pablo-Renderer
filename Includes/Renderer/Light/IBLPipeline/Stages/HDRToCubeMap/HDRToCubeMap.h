//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_HDRTOCUBEMAP_H
#define PABLO_RENDERER_HDRTOCUBEMAP_H

#include "Renderer/Light/IBLPipeline/Stages/BaseStage.h"

class HDRToCubeMap:public BaseStage {
public:
    HDRToCubeMap();

protected:
    TextureBase execute(TextureBase input) override;
};


#endif //PABLO_RENDERER_HDRTOCUBEMAP_H
