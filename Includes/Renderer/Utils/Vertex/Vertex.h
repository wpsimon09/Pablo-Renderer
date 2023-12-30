//
// Created by wpsimon09 on 30/12/23.
//

#ifndef CLIONTEST_VERTEX_H
#define CLIONTEST_VERTEX_H

#include "Shader.h"
#include "glm/glm.hpp"
#include <cstddef> // Include for offsetof


class Vertex {
public:
    glm::vec3 position;
    glm::vec3 normals;
    glm::vec2 uv;
    glm::vec3 tangent;
    glm::vec3 bitangent;

    Vertex() = default;
    Vertex(glm::vec3 pos, glm::vec2 uvs,glm::vec3 norm = glm::vec3(0.0f),  glm::vec3 tang = glm::vec3(0.0f), glm::vec3 bitang = glm::vec3(0.0f));
    virtual ~Vertex();
};


#endif //CLIONTEST_VERTEX_H
