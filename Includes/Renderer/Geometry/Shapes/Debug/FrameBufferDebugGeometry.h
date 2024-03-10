//
// Created by wpsimon09 on 06/02/24.
//

#ifndef PABLO_RENDERER_FRAMEBUFFERDEBUGGEOMETRY_H
#define PABLO_RENDERER_FRAMEBUFFERDEBUGGEOMETRY_H

#include "Renderer/Geometry/Geometry.h"

/***
 * Represents geometry of the small square that server as placeholder for displaying color attachment of the GL_FRAMEBUFFER
 */
class FrameBufferDebugGeometry : public Geometry {
public:
    /***
     * Creates the instance of the frame buffer debug geometry
     */
    FrameBufferDebugGeometry();
};


#endif //PABLO_RENDERER_FRAMEBUFFERDEBUGGEOMETRY_H
