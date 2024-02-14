//
// Created by wpsimon09 on 08/02/24.
//

#ifndef PABLO_RENDERER_GRID_H
#define PABLO_RENDERER_GRID_H

#include "Renderer/Renderable/Renderable.h"
#include "Renderer/Utils/FrameBuffer/FrameBuffer.h"
#include "Renderer/Geometry/Shapes/GridPlane/GridGeometry.h"
#include "Renderer/Material/BasicMaterialColor/BasicMaterialColor.h"

class Grid: public Renderable {
public:
    explicit Grid();
private:
    Shader* mainShader;
};



#endif //PABLO_RENDERER_GRID_H
