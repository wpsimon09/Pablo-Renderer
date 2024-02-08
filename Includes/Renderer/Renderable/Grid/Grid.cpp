//
// Created by wpsimon09 on 08/02/24.
//

#include "Grid.h"

Grid::Grid():Renderable() {
    this->name = "Grid";
    this->procedularTextureShadaer = new Shader("VertexShader/FloorGridVertex.glsl", "FragmentShader/FloorGridFragment.glsl", "Procedural grid texture shader");
    this->mainShader = new Shader("VertexShader/FloorVertex.glsl", "FragmentShader/FloorFragment.glsl", "floor");
    this->frameBuffer = new FrameBuffer(600, 800);
    this->frameBuffer->setShader(procedularTextureShadaer);
    this->objectGeometry = new HugePlane();
    this->frameBuffer->setGeometry(this->objectGeometry);
    this->frameBuffer->drawInsideSelf();
    this->objectMaterial = new BasicMaterialTextured(mainShader, frameBuffer->getRenderedResult(), "texture_diffuse0");
}
