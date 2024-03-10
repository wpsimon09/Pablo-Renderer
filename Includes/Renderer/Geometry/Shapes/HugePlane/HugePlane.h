//
// Created by wpsimon09 on 08/02/24.
//

#ifndef PABLO_RENDERER_HUGEPLANE_H
#define PABLO_RENDERER_HUGEPLANE_H

#include "Renderer/Geometry/Geometry.h"

/***
 * Geometry representing plane that spans through 200m
 */
class HugePlane: public Geometry {
public:
    /***
     * Creates an instance of the Huge Plane geometry
     * @param name name for the geometry instance
     */
    explicit HugePlane(std::string name = "huge plane");
};


#endif //PABLO_RENDERER_HUGEPLANE_H
