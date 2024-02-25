//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_IRRADIANCE_H
#define PABLO_RENDERER_IRRADIANCE_H
#include "Renderer/Light/IBLPipeline/Stages/BaseStage.h"

class Irradiance:public BaseStage {
public:
    Irradiance();
    void execute(TextureBase input) override;
    std::shared_ptr<Texture3D> result;
private:
    std::unique_ptr<FrameBufferCube> frameBufferCube;
};


#endif //PABLO_RENDERER_IRRADIANCE_H
