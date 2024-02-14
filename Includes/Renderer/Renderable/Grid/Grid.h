//
// Created by wpsimon09 on 08/02/24.
//

#ifndef PABLO_RENDERER_GRID_H
#define PABLO_RENDERER_GRID_H

#include "Renderer/Renderable/Renderable.h"
#include "Renderer/Utils/FrameBuffer/FrameBuffer.h"
#include "Renderer/Geometry/Shapes/HugePlane/HugePlane.h"
#include "Renderer/Material/BasicMaterialTexturd/BasicMaterialTextured.h"

class Grid: public Renderable {
public:
    explicit Grid();
private:
    Texture2D generatedTexture;
    FrameBuffer* frameBuffer;
    Shader* procedularTextureShadaer;
    Shader* mainShader;
};



#endif //PABLO_RENDERER_GRID_H
