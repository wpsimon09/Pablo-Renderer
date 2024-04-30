//
// Created by wpsimon09 on 08/02/24.
//

#include "Grid.h"

Grid::Grid():Renderable(){
    this->name = "Grid";
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!----------------- CHECK FOR OWNER SHIP HERE -----------------------!!!!!!!!!!!!!!!!!!!!!!!!!!!!§
    this->mainShader = std::make_unique<Shader>("VertexShader/FloorVertex.glsl", "FragmentShader/FloorFragment.glsl", "floor");

    this->objectMaterial = std::make_unique<BasicMaterialColor>();
    this->objectGeometry = std::make_unique<GridGeometry>();
    //this->objectMaterial = new BasicMaterialTextured(mainShader, "Assets/Textures/AdvancedLightning/grid_ch.png", "texture_diffuse0");
}

