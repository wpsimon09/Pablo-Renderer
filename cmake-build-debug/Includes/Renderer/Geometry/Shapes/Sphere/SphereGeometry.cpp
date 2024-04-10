//
// Created by wpsimon09 on 15/03/24.
//

#include "SphereGeometry.h"

#include <utility>

SphereGeometry::SphereGeometry(std::string name, unsigned int quality): Geometry() {
    this->name = std::move(name);
    this->vao = generateSpeher(quality);
    this->shapes = GL_TRIANGLE_STRIP;
    this->numIndecies = this->vao->getNumberOfIndecies();
    this->numVerticies = this->vao->getNumberOfVerticies();
}

std::unique_ptr<VAO> SphereGeometry::generateSpeher(unsigned int quality) {
    std::vector<Vertex> verticies;
    std::vector<unsigned int> indices;

    const unsigned int X_SEGMENTS = quality;
    const unsigned int Y_SEGMENTS = quality;
    const float PI = 3.14159265359f;
    for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
    {
        for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
        {
            Vertex tempVertex;
            float xSegment = (float)x / (float)X_SEGMENTS;
            float ySegment = (float)y / (float)Y_SEGMENTS;
            float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            float yPos = std::cos(ySegment * PI);
            float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            tempVertex.position = glm::vec3(xPos, yPos, zPos);
            tempVertex.uv = glm::vec2(xSegment, ySegment);
            tempVertex.normals = glm::vec3(xPos, yPos, zPos);

            verticies.push_back(tempVertex);
        }
    }

    bool oddRow = false;
    for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
    {
        if (!oddRow)
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                indices.push_back(y * (X_SEGMENTS + 1) + x);
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            }
        }
        else
        {
            for (int x = X_SEGMENTS; x >= 0; --x)
            {
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                indices.push_back(y * (X_SEGMENTS + 1) + x);
            }
        }
        oddRow = !oddRow;
    }

    return std::make_unique<VAO>(verticies, indices);
}

void SphereGeometry::render() const {
    this->vao->bind();
    glDrawElements(this->shapes, this->numIndecies, GL_UNSIGNED_INT, 0);
    glCheckError();

    this->vao->unbind();
}
