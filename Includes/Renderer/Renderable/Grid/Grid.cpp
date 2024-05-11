//
// Created by wpsimon09 on 08/02/24.
//

#include "Grid.h"

Grid::Grid():Renderable(){
    this->name = "Grid";
    this->objectMaterial = std::make_unique<BasicMaterialColor>(glm::vec3(1.0f));
    this->objectMaterial->shader = std::make_shared<Shader>("VertexShader/FloorVertex.glsl", "FragmentShader/FloorFragment.glsl", "floor");
    this->objectGeometry = std::make_unique<GridGeometry>();
    //this->objectMaterial = new BasicMaterialTextured(mainShader, "Assets/Textures/AdvancedLightning/grid_ch.png", "texture_diffuse0");
}

