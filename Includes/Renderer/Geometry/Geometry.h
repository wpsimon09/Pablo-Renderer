//
// Created by wpsimon09 on 30/12/23.
//

#ifndef CLIONTEST_GEOMETRY_H
#define CLIONTEST_GEOMETRY_H

#include "vector"
#include "Renderer/Utils/Vertex/Vertex.h"
class Geometry {
public:
    GLuint getVertexArrays();
    std::string getName();
    virtual ~Geometry(){};
protected:
    std::string name;
    GLuint VAO;
    GLuint VBO;
    virtual void generateVAO() {};
    virtual void fillTheVerticies() {};
};


#endif //CLIONTEST_GEOMETRY_H
