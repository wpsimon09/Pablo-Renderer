//
// Created by wpsimon09 on 06/02/24.
//

#ifndef PABLO_RENDERER_FRAMEBUFFERDEBUG_H
#define PABLO_RENDERER_FRAMEBUFFERDEBUG_H

#include "Renderer/Utils/FrameBuffer/FrameBuffer.h"
#include "Renderer/Geometry/Shapes/Debug/FrameBufferDebugGeometry.h"

class FrameBufferDebug: public FrameBuffer {
public:
    FrameBufferDebug(int width, int height);
    void changeTexture(TextureBase texture);
};


#endif //PABLO_RENDERER_FRAMEBUFFERDEBUG_H
