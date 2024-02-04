//
// Created by wpsimon09 on 04/02/24.
//

#ifndef PABLO_RENDERER_GRID_H
#define PABLO_RENDERER_GRID_H

#include "Renderer/SceneGraph/SceneNode/SceneNode.h"
#include "Shader.h"
#include "Renderer/Geometry/Geometry.h"
#include "Renderer/Geometry/Shapes/Plane/PlaneGeometry.h"

class Grid : public SceneNode{
public:
    Grid(Shader* shader);
};


#endif //PABLO_RENDERER_GRID_H
