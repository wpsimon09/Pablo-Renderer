//
// Created by wpsimon09 on 30/12/23.
//

#include "VAO.h"
#include "Debug/DebugLogger.h"

//loading with numVerticies must have everything
VAO::VAO(std::vector<Vertex> vertecies, std::vector<unsigned int>indecies) {
    glGenVertexArrays(1, &this->ID);
    glCheckError();

    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);
    glCheckError();

    this->bind();

    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glCheckError();

    glBufferData(GL_ARRAY_BUFFER, vertecies.size() * sizeof(Vertex), &vertecies[0], GL_STATIC_DRAW);
    glCheckError();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glCheckError();

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indecies.size() * sizeof(unsigned int), &indecies[0], GL_STATIC_DRAW);
    glCheckError();

    this->hasPositions = true;
    this->hasTexCoords = true;
    this->hasNormals = true;
    this->hasTangents = true;
    this->hasBitangents = true;
    indecies.size() > 1 ? this->hasEBO = true : this->hasEBO = false;

    //vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));
    glCheckError();

    //noramls
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));
    glCheckError();

    //textures
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));
    glCheckError();

    //tangents
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));
    glCheckError();

    //bytangents
    glEnableVertexAttribArray(4);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, bitangent));
    glCheckError();

    this->unbind();
    glCheckError();

}

//loading via normal array
VAO::VAO(float *vertecies, float numberOfComponents, bool hasNormals, bool hasTexCoords) {
    glGenVertexArrays(1, &this->ID);
    glGenBuffers(1, &this->VBO);
    glBindVertexArray(this->ID);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfComponents , vertecies, GL_STATIC_DRAW);

    this->hasPositions = true;
    this->hasTexCoords = true;
    this->hasNormals = true;

    this->hasEBO = false;
    this->hasBitangents = false;
    this->hasTangents = false;


    std::cout << "Sizeof vertecies:" << sizeof(float) * numberOfComponents << "bytes" << std::endl;

    if (hasNormals && hasTexCoords)
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

        std::cout << "Created object has 3 vertex atributes" << std::endl;
        std::cout << "0 - positions (vec3)" << std::endl;
        std::cout << "1 - normal vectors (vec3)" << std::endl;
        std::cout << "2 - texture coordinates (vec2)" << std::endl;
    }
    if (hasNormals && !hasTexCoords)
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

        this->hasTexCoords = false;

        std::cout << "Created object has 2 vertex atributes" << std::endl;
        std::cout << "0 - positions (vec3)" << std::endl;
        std::cout << "1 - normal vectors (vec3)" << std::endl;
    }
    if (!hasNormals && hasTexCoords)
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

        this->hasNormals = false;

        std::cout << "Created object has 2 vertex atributes" << std::endl;
        std::cout << "0 - positions (vec3)" << std::endl;
        std::cout << "2 - texture coordinates (vec2)" << std::endl;
    }
    if (!hasNormals && !hasTexCoords)
    {
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        this->hasTexCoords=false;
        this->hasNormals=false;

        std::cout << "Created object has 1 vertex atribute" << std::endl;
        std::cout << "0 - positions (vec3)" << std::endl;
    }

    std::cout << std::endl;
    glBindVertexArray(0);
}

void VAO::unbind() {
    glBindVertexArray(0);
    glCheckError();
}

void VAO::bind() {
    glBindVertexArray(this->ID);
    glCheckError();
}

void VAO::getStatus() {
    std::cout<<"Created vao has the following options"<<std::endl;
    std::cout<<"Has positions: "<<this->hasPositions<<std::endl;
    std::cout<<"Has normals: "<<this->hasNormals<<std::endl;
    std::cout<<"Has UV coordinates: "<<this->hasTexCoords<<std::endl;
    std::cout<<"Has tangents: "<<this->hasTangents<<std::endl;
    std::cout<<"Has bitangents: "<<this->hasBitangents<<std::endl;
    std::cout<<"Has Element buffer object: "<<this->hasEBO<<std::endl;
}


