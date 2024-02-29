//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_BRDF_H
#define PABLO_RENDERER_BRDF_H

#include "Renderer/Light/IBLPipeline/Stages/BaseStage.h"
class BRDF: public BaseStage{
public:
    BRDF();
    void execute();
    std::shared_ptr<Texture2D>result;
protected:
    std::unique_ptr<FrameBuffer> frameBuffer;
};


#endif //PABLO_RENDERER_BRDF_H
