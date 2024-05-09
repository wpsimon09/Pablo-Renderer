//
// Created by wpsimon09 on 30/12/23.
//

#ifndef CLIONTEST_VAO_H
#define CLIONTEST_VAO_H
#include "glad.h"
#include "Renderer/Utils/Vertex/Vertex.h"
#include "vector"
#include "Renderer/Utils/OGLObject/OGLObject.h"
#include "Debug/DebugLogger.h"


class VAO: public OGLObject{
public:
    GLuint ID;
    bool hasNormals;
    bool hasTexCoords;
    bool hasPositions;
    bool hasTangents;
    bool hasBitangents;
    bool hasEBO;
    VAO(std::vector<Vertex> vertecies, std::vector<unsigned  int> indecies = {});
    VAO(float vertecies[], float numberOfComponents, bool hasNormals = true, bool hasTexCoords = true);

    void bind() override;
    void unbind() override;


    void getStatus();
    unsigned int getNumberOfIndecies();
    unsigned int getNumberOfVerticies();
private:
    unsigned int numOfIndecies = 0;
    unsigned int numOfVerticies = 0;

    GLuint VBO;
    GLuint EBO;
};


#endif //CLIONTEST_VAO_H
