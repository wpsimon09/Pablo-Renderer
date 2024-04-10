//
// Created by wpsimon09 on 31/12/23.
//

#ifndef PABLO_RENDERER_SCREENSPACEQUADGEOMETRY_H
#define PABLO_RENDERER_SCREENSPACEQUADGEOMETRY_H

#include "Renderer/Geometry/Geometry.h"

/***
 * Geometry representing the whole screen mostly used for FrameBuffer rendering
 */
class ScreenSpaceQuadGeometry: public Geometry {
public:
    /***
     * Creates an instance of the Screen space quad geometry
     * @param name name for the geometry
     */
    explicit ScreenSpaceQuadGeometry(std::string name = "SCREEN SPACE QUAD");
};


#endif //PABLO_RENDERER_SCREENSPACEQUADGEOMETRY_H
