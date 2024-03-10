//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_BRDF_H
#define PABLO_RENDERER_BRDF_H

#include "Renderer/Light/IBLPipeline/Stages/BaseStage.h"

/***
 * Generates the look up texture for Bidirectional Reflectance Distribution Function
 */
class BRDF: public BaseStage{
public:
    BRDF();
    /***
     * Executes the stage without any input
     */
    void execute();

    /***
     * Stored result of the execution
     */
    std::shared_ptr<Texture2D>result;
protected:
    std::unique_ptr<FrameBuffer> frameBuffer;
};


#endif //PABLO_RENDERER_BRDF_H
