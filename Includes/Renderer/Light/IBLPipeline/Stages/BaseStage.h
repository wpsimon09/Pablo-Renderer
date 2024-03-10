//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_BASESTAGE_H
#define PABLO_RENDERER_BASESTAGE_H

#include "Renderer/Utils/FrameBuffer/FrameBufferCube/FrameBufferCube.h"
#include "Renderer/Utils/Texture/TextureBase.h"

/***
 * Stage of the IBL pipeline that is meant to be inherited by concrete steps
 */
class BaseStage {
protected:
    BaseStage() =default ;

    /***
     * Shader for the concrete stege
     */
    std::shared_ptr<Shader> shader;
public:
    /***
     * Executes the concrete stage
     * @param input input texture should be HDR texture or HDR converted to cube map
     */
    virtual void execute(TextureBase input){};
};


#endif //PABLO_RENDERER_BASESTAGE_H
