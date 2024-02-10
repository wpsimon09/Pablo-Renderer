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
    Grid();
private:
    //create generated texture here and pass it to the frame buffer
    Texture2D* generatedGrid;
    //aso make the framebuffe accept the new texture in to constructor
    //either pass texture widh and height as parameter or store it inside Tecture2D class
    //alternativly chceck how to return textures in common mistakes in open gl
    s
    void generateTexture();
    FrameBuffer* frameBuffer;
    Shader* procedularTextureShadaer;
    Shader* mainShader;
};


#endif //PABLO_RENDERER_GRID_H
