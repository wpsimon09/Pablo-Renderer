//
// Created by wpsimon09 on 06/02/24.
//

#ifndef PABLO_RENDERER_DEBUGFRAMEBUFFERPLANEDATA_H
#define PABLO_RENDERER_DEBUGFRAMEBUFFERPLANEDATA_H

float frameBufferDebugPlane[] = {
        // positions                            // texture Coords
        0.30f,  0.40f, 0.0f, 0.0f, 0.0f, // bottom left
        0.30f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // top right

        0.30f,  0.40f, 0.0f, 0.0f, 0.0f, // bottom left
        1.0f, 0.40f, 0.0f, 1.0f, 0.0f, // bottom right
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // top right
};


#endif //PABLO_RENDERER_DEBUGFRAMEBUFFERPLANEDATA_H
