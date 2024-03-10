//
// Created by wpsimon09 on 06/02/24.
//

#ifndef PABLO_RENDERER_FRAMEBUFFERDEBUG_H
#define PABLO_RENDERER_FRAMEBUFFERDEBUG_H

#include "Renderer/Utils/FrameBuffer/FrameBuffer.h"
#include "Renderer/Geometry/Shapes/Debug/FrameBufferDebugGeometry.h"

/***
 * Represent debug frame buffer which is inherited from FrameBuffer class
 * Only difference is in the geometry of the FrameBuffer which is set to debug frame buffer geometry
 * @inherit FrameBuffer
 */
class FrameBufferDebug: public FrameBuffer {
public:
    FrameBufferDebug(int width, int height);

    /***
     * Change the texture we want to display
     * @param texture new texture to be displayed
     */
    void changeTexture(TextureBase texture);
};

#endif //PABLO_RENDERER_FRAMEBUFFERDEBUG_H