//
// Created by wpsimon09 on 30/12/23.
//

#ifndef CLIONTEST_RENDERABLE_H
#define CLIONTEST_RENDERABLE_H

#include "Renderer/Utils/Vertex/Vertex.h"
#include "vector"
#include "Shader.h"
#include "glm/glm.hpp"
#include "Renderer/Utils/Transformations/Transformations.h"

class Renderable {
private:
    std::vector<Vertex> vertices;
    Shader* shader;
    Transformations transformations;
};


#endif //CLIONTEST_RENDERABLE_H
