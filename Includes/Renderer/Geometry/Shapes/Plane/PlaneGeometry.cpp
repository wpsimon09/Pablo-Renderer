//
// Created by wpsimon09 on 30/12/23.
//

#include "PlaneGeometry.h"
#include "planeVertexData.h"

PlaneGeometry::PlaneGeometry(std::string name): Geometry() {
    this->name = std::move(name);
    this->generateVerticies();
    this->vao = std::make_unique<VAO>(this->planeVertices);
    this->shapes = GL_TRIANGLES;
    this->numVerticies = 6;
}

void PlaneGeometry::generateVerticies() {
    // Triangle 1
    planeVertices.push_back(Vertex(glm::vec3(1.0f, -0.5f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    planeVertices.push_back(Vertex(glm::vec3(-1.0f, -0.5f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    planeVertices.push_back(Vertex(glm::vec3(-1.0f, -0.5f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));

    // Triangle 2
    planeVertices.push_back(Vertex(glm::vec3(1.0f, -0.5f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    planeVertices.push_back(Vertex(glm::vec3(-1.0f, -0.5f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
    planeVertices.push_back(Vertex(glm::vec3(1.0f, -0.5f, -1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
}

