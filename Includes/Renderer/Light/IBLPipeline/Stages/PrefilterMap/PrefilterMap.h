//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_PREFILTERMAP_H
#define PABLO_RENDERER_PREFILTERMAP_H

#include "Renderer/Light/IBLPipeline/Stages/BaseStage.h"

class PrefilterMap:public BaseStage {
public:
    PrefilterMap();
    void execute(TextureBase input) override;
    std::shared_ptr<Texture3D> result;
protected:
    std::unique_ptr<FrameBufferCube> frameBufferCube;
};


#endif //PABLO_RENDERER_PREFILTERMAP_H
