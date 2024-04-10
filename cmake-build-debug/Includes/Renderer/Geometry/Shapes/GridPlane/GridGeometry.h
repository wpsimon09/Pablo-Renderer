//
// Created by wpsimon09 on 14/02/24.
//

#ifndef PABLO_RENDERER_GRIDGEOMETRY_H
#define PABLO_RENDERER_GRIDGEOMETRY_H

#include "Renderer/Geometry/Geometry.h"

/***
 * Creates a grid formed with lines
 */
class GridGeometry:public Geometry{
public:
    /***
     * Creates instance of the gird geomtry
     * @param size size of the grid
     * @param divisions number of divisions
     */
    explicit GridGeometry(float size = 400.0f, int divisions = 80);
};


#endif //PABLO_RENDERER_GRIDGEOMETRY_H
