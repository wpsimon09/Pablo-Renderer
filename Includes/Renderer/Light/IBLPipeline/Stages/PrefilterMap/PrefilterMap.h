//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_PREFILTERMAP_H
#define PABLO_RENDERER_PREFILTERMAP_H

#include "Renderer/Light/IBLPipeline/Stages/BaseStage.h"

/***
 * Stage that creates different textures for different rougness levels and stores it as mip maps
 */
class PrefilterMap:public BaseStage {
public:
    PrefilterMap();
    /***
     * Executes the concrete stage
     * @param input Should be cube map representation fo the equirectangular map
     */
    void execute(TextureBase input) override;

    /***
     * Results of concrete stage
     */
    std::shared_ptr<Texture3D> result;
protected:
    /***
     * Frame buffer when actual rendering takes place and results are initially stored inside the frame buffer's color attachment
     */
    std::unique_ptr<FrameBufferCube> frameBufferCube;
};


#endif //PABLO_RENDERER_PREFILTERMAP_H
