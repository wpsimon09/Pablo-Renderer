//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_IRRADIANCE_H
#define PABLO_RENDERER_IRRADIANCE_H
#include "Renderer/Light/IBLPipeline/Stages/BaseStage.h"

/***
 * Class responsible for generating irradiance map
 */
class Irradiance:public BaseStage {
public:
    Irradiance();

    /***
     * Executes the concrete stage
     * @param input Should be cube map representation fo the equirectangular map
     */
    void execute(TextureBase input) override;

    /***
     * Stored result of the concrete stage
     */
    std::shared_ptr<Texture3D> result;
private:
    std::unique_ptr<FrameBufferCube> frameBufferCube;
};


#endif //PABLO_RENDERER_IRRADIANCE_H
