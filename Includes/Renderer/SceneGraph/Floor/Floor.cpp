//
// Created by wpsimon09 on 04/02/24.
//

#include "Floor.h"

Floor::Floor(): SceneNode(){
    this->shader = std::make_unique<Shader>("VertexShader/PBR/PBRVertex.glsl", "FragmentShader/PBR/PBR-FloorFragment.glsl", "PBR floor");
    std::unique_ptr<Material> mat = std::make_unique<PBRTextured>(std::move(shader),"Assets/Textures/PBR/ForestRock");
    std::unique_ptr<Geometry> geometry = std::make_unique<PlaneGeometry>();
    std::unique_ptr<Renderable> gridRenderable = std::make_unique<Renderable>(std::move(geometry),std::move(mat));
    this->addChild(std::make_unique<SceneNode>(std::move(gridRenderable)));
}



