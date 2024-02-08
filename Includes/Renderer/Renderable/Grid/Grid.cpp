//
// Created by wpsimon09 on 08/02/24.
//

#include "Grid.h"

Grid::Grid():Renderable() {
    this->name = "Grid";
    this->procedularTextureShadaer = new Shader("VertexShader/FloorGridVertex.glsl", "FragmentShader/FloorGridFragment.glsl", "Procedural grid texture shader");
    this->procedularTextureShadaer->use();
    this->procedularTextureShadaer->setFloat("numOfDivisions", 2);
    this->mainShader = new Shader("VertexShader/FloorVertex.glsl", "FragmentShader/FloorFragment.glsl", "floor");
    this->frameBuffer = new FrameBuffer(600, 800);
    this->frameBuffer->setShader(procedularTextureShadaer);
    this->frameBuffer->drawInsideSelf();
    this->objectGeometry = new HugePlane();
    this->objectMaterial = new BasicMaterialTextured(mainShader, frameBuffer->getRenderedResult(), "texture_diffuse0");
}
