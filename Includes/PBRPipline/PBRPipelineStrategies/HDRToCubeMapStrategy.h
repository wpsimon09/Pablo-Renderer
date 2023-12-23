//
// Created by wpsimon09 on 23/12/23.
//

#ifndef CLIONTEST_HDRTOCUBEMAPSTRATEGY_H
#define CLIONTEST_HDRTOCUBEMAPSTRATEGY_H

#include "PBRPipline/FrameBufferStrategy/FrameBufferStrategy.h"
#include "Texture/Texture.h"
#include "FrameBuffer/FrameBuffer.h"

class HDRToCubeMapStrategy: FrameBufferStrategy{
public:
    void drawToTexture(FrameBuffer *frameBuffer, Texture *texture) const override;

};


#endif //CLIONTEST_HDRTOCUBEMAPSTRATEGY_H
