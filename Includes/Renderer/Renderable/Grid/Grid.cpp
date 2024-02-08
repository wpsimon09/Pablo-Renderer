//
// Created by wpsimon09 on 08/02/24.
//

#include "Grid.h"

Grid::Grid() {
    this->procedularTextureShadaer = new Shader("VertexShader/FloorGridVertex.glsl", "FragmentShader/FloorGridFragment.glsl", "Procedural grid texture shader");
    this->mainShader = new Shader("VertexShader/FloorVertex.glsl", "FragmentShader/FloorFragment.glsl", "floor");
    this->frameBuffer = new FrameBuffer(1200, 1200);
    this->frameBuffer->setShader(procedularTextureShadaer);
    this->frameBuffer->drawInsideSelf();
    this->objectGeometry =
}
