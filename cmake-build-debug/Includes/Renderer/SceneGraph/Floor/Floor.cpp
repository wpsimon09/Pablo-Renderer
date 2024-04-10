//
// Created by wpsimon09 on 04/02/24.
//

#include "Floor.h"

Floor::Floor(): SceneNode(){
    auto floorShader = std::make_shared<Shader>("VertexShader/PBR/PBRVertex.glsl", "FragmentShader/PBR/PBR-FloorFragment.glsl", "PBR floor");
    auto mat = std::make_unique<PBRTextured>(floorShader,"Assets/Textures/PBR/ForestRock");
    auto geometry = std::make_unique<PlaneGeometry>();
    auto floorRenderable = std::make_unique<Renderable>(std::move(geometry), std::move(mat));
    this->addChild(std::make_unique<SceneNode>(std::move(floorRenderable)));
    this->transformation->setScale(glm::vec3(5.0f, 1.0f, 5.0f));
}



