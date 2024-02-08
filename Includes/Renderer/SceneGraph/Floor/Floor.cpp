//
// Created by wpsimon09 on 04/02/24.
//

#include "Floor.h"

Floor::Floor(): SceneNode(){
    this->shader = new Shader("VertexShader/PBR/PBRVertex.glsl", "FragmentShader/PBR/PBR-FloorFragment.glsl", "PBR floor");
    Material* mat = new PBRTextured(shader,"Assets/Textures/PBR/ForestRock");
    Geometry* geometry = new PlaneGeometry();
    Renderable* gridRenderable = new Renderable(geometry, mat);
    this->addChild(new SceneNode(gridRenderable));
}



