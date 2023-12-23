//
// Created by wpsimon09 on 23/12/23.
//

#ifndef CLIONTEST_FRAMEBUFFERSTRATEGY_H
#define CLIONTEST_FRAMEBUFFERSTRATEGY_H

#include "FrameBuffer/FrameBuffer.h"
#include "Texture/Texture.h"

class FrameBufferStrategy {
public:
    virtual void drawToTexture(FrameBuffer *frameBuffer, Texture *texture) const{};
};


#endif //CLIONTEST_FRAMEBUFFERSTRATEGY_H
