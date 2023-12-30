//
// Created by wpsimon09 on 30/12/23.
//

#include "Vertex.h"

Vertex::Vertex(glm::vec3 pos, glm::vec2 uvs, glm::vec3 norm, glm::vec3 tang, glm::vec3 bitang) {
    this->position = pos;
    this->normals = norm;
    this->uv = uvs;
    this->tangent = tang;
    this->bitangent = bitang;
}

Vertex::~Vertex() {
    this->position = {0.0f, 0.0f, 0.0f};
    this->uv = {0.0f, 0.0f};
    this->normals = {0.0f, 0.0f, 0.0f};
    this->tangent = {0.0f, 0.0f, 0.0f};
    this->bitangent = {0.0f, 0.0f, 0.0f};
}


