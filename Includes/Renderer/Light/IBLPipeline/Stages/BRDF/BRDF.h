//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_BRDF_H
#define PABLO_RENDERER_BRDF_H

#include "Renderer/Light/IBLPipeline/Stages/BaseStage.h"

/***
 * Generates the look up texture for Bidirectional Reflectance Distribution Function
 * @inherit Base stage
 */
class BRDF: public BaseStage{
public:
    BRDF();

    /***
     * Executes the stage
     * @param input this input has no impact on the rendering and is not used
     */
    void execute(TextureBase input) override;

protected:
    std::unique_ptr<FrameBuffer> frameBuffer;
};


#endif //PABLO_RENDERER_BRDF_H
