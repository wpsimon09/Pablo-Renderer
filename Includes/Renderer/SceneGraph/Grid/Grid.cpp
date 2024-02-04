//
// Created by wpsimon09 on 04/02/24.
//

#include "Grid.h"

Grid::Grid(Shader *shader): SceneNode(){
    Material* mat = new PBRColor(shader);
    Geometry* geometry = new PlaneGeometry();
    Renderable* gridRenderable = new Renderable(geometry, mat);
    this->addChild(new SceneNode(gridRenderable));
}

