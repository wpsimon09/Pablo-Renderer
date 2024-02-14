//
// Created by wpsimon09 on 08/02/24.
//

#include "Grid.h"

Grid::Grid():Renderable(){
    this->name = "Grid";
    this->procedularTextureShadaer = new Shader("VertexShader/FloorGridVertex.glsl", "FragmentShader/FloorGridFragment.glsl", "Procedural grid texture shader");
    this->mainShader = new Shader("VertexShader/FloorVertex.glsl", "FragmentShader/FloorFragment.glsl", "floor");
    this->frameBuffer = new FrameBuffer(512, 512);

    this->frameBuffer->setShader(procedularTextureShadaer);
    this->frameBuffer->drawInsideSelf();
    this->frameBuffer->getRenderedResult().changeFilteringMethod(GL_REPEAT, GL_REPEAT);

    this->generatedTexture = frameBuffer->getRenderedResult();

    this->generatedTexture.setSamplerID(0);

    this->objectMaterial = new BasicMaterialTextured(mainShader, this->frameBuffer->getRenderedResult(), "texture_diffuse0");
    this->objectGeometry = new GridGeometry();
    //this->objectMaterial = new BasicMaterialTextured(mainShader, "Assets/Textures/AdvancedLightning/grid_ch.png", "texture_diffuse0");
}

