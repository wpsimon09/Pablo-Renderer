//
// Created by wpsimon09 on 14/02/24.
//

#include "GridGeometry.h"

GridGeometry::GridGeometry(float size, int divisions) : Geometry() {
    std::vector<float> vertices;

    float step = size / divisions;

    for (int i = -divisions; i <= divisions; ++i) {
        vertices.push_back(i * step);
        vertices.push_back(0.0f);
        vertices.push_back(-size);
        vertices.push_back(i * step);
        vertices.push_back(0.0f);
        vertices.push_back(size);
        vertices.push_back(-size);
        vertices.push_back(0.0f);
        vertices.push_back(i * step);
        vertices.push_back(size);
        vertices.push_back(0.0f);
        vertices.push_back(i * step);
    }

    float vertexData[vertices.size()];

    std::copy(vertices.begin(), vertices.end(), vertexData);

    this->vao = std::make_unique<VAO>(vertices.data(), sizeof(vertexData) / sizeof(float), false, false);
    this->shapes = GL_LINES;
    this->name = "GRID";
    this->numVerticies = vertices.size() / 3;
    this->numIndecies = 0;
}
