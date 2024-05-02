//
// Created by wpsimon09 on 30/12/23.
//

#ifndef PABLO_RENDERER_PLANEGEOMETRY_H
#define PABLO_RENDERER_PLANEGEOMETRY_H

#include "Renderer/Geometry/Geometry.h"


/***
 * Class representing geometry of the plane
 */
class PlaneGeometry: public Geometry {
public:
    /***
     * Creates an instance of the PalneGeometry class
     * @param name name for the geometry default is "plane"
     */
    explicit PlaneGeometry(std::string name = "plane");

    std::vector<glm::vec3>getAreaLightEdgePoints();

};


#endif //PABLO_RENDERER_PLANEGEOMETRY_H
