//
// Created by wpsimon09 on 30/12/23.
//

#ifndef CLIONTEST_GEOMETRY_H
#define CLIONTEST_GEOMETRY_H

#include "glad/glad.h"
#include "vector"
#include "Renderer/Utils/Vertex/Vertex.h"
#include "Renderer/Utils/VAO/VAO.h"


class Geometry {
public:
    GLuint getVertexArrays() const ;
    void bindVertexArrays() const;
    void unbindVertexArrays() const;
    std::string getName() const;
    virtual ~Geometry(){};
protected:
    unsigned int verticies;
    unsigned int indecies;
    GLenum shapes;
    std::string name;
    VAO *vao;
public:
    unsigned int getVerticies(){return this->verticies;}
    void setVerticies(unsigned int verticies){this->verticies = verticies;}

    unsigned int getIndecies(){return this->indecies;}
    void setIndecies(unsigned int indecies){this->indecies = indecies;}

    GLenum getDrawingType(){return this->shapes;}
    void setDrawingType(GLenum shapes){this->shapes = shapes;}
};


#endif //CLIONTEST_GEOMETRY_H
