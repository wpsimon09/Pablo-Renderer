//
// Created by wpsimon09 on 15/02/24.
//

#ifndef PABLO_RENDERER_BASESTAGE_H
#define PABLO_RENDERER_BASESTAGE_H

#include "Renderer/Utils/FrameBuffer/FrameBufferCube/FrameBufferCube.h"
#include "Renderer/Utils/Texture/TextureBase.h"
class BaseStage {
protected:
    BaseStage() =default ;
    std::unique_ptr<Shader> shader;
public:
    virtual void execute(std::unique_ptr<TextureBase> input){};
};


#endif //PABLO_RENDERER_BASESTAGE_H
