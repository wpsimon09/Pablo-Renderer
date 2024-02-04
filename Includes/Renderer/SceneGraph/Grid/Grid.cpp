//
// Created by wpsimon09 on 04/02/24.
//

#include "Grid.h"

Grid::Grid(): SceneNode() {
    Shader shader("VertexShader/PBR/PBRVertex.glsl", "FragmentShader/PBR/PBRFragment.glsl", "PBR shader2");
    Material* mat = new PBRColor(&shader);
    Geometry* geometry = new PlaneGeometry();
    Renderable* gridRenderable = new Renderable(geometry, mat);
    this->addChild(new SceneNode(gridRenderable));
}
