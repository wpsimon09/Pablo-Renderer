//
// Created by wpsimon09 on 31/12/23.
//

#ifndef PABLO_RENDERER_MODELGEOMETRY_H
#define PABLO_RENDERER_MODELGEOMETRY_H

#include "Renderer/Geometry/Geometry.h"
#include "vector"
#include "Model.h"


class ModelGeometry: public Geometry{
public:
    explicit ModelGeometry(std::string name, std::vector<Vertex> verticies, std::vector<unsigned int>indecies = {0});
    explicit ModelGeometry(const char* pathToTheModel);

    void render() const override;

private:
};


#endif //PABLO_RENDERER_MODELGEOMETRY_H
