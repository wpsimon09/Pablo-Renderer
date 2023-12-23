//
// Created by wpsimon09 on 23/12/23.
//

#include "HDRToCubeMapStrategy.h"

void HDRToCubeMapStrategy::drawToTexture(FrameBuffer *frameBuffer, Texture *texture) const  {
    frameBuffer->use();
    frameBuffer->mountTexture(texture);

}