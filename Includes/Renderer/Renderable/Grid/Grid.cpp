//
// Created by wpsimon09 on 08/02/24.
//

#include "Grid.h"

Grid::Grid():Renderable() {
    this->name = "Grid";
    this->procedularTextureShadaer = new Shader("VertexShader/FloorGridVertex.glsl", "FragmentShader/FloorGridFragment.glsl", "Procedural grid texture shader");
    this->mainShader = new Shader("VertexShader/FloorVertex.glsl", "FragmentShader/FloorFragment.glsl", "floor");
    this->objectGeometry = new HugePlane("Huge plane");
    this->frameBuffer = new FrameBuffer(800, 600);
    this->generateTexture();
    this->objectMaterial = new BasicMaterialTextured(mainShader, std::move(this->frameBuffer->getRenderedResult()), "texture_diffuse0");
    //this->objectMaterial = new BasicMaterialTextured(mainShader, "Assets/Textures/AdvancedLightning/grid_ch.png", "texture_diffuse0");
}

void Grid::generateTexture() {
    this->frameBuffer->setShader(procedularTextureShadaer);
    this->frameBuffer->drawInsideSelf();
    this->frameBuffer->getRenderedResult().setSamplerID(0);
}
