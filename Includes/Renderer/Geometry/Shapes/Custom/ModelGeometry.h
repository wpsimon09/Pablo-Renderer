//
// Created by wpsimon09 on 31/12/23.
//

#ifndef MODELGEOMETRY_H
#define MODELGEOMETRY_H

#include "Renderer/Geometry/Geometry.h"
#include "vector"

class ModelGeometry: public Geometry{
public:
    explicit ModelGeometry(std::string name, std::vector<Vertex> verticies, std::vector<unsigned int>indecies = {0});

    void render() const override;

private:
};

#endif //PABLO_RENDERER_MODELGEOMETRY_H
