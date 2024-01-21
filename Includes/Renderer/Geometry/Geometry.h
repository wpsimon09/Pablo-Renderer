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
    virtual void render() const;
protected:
    unsigned int numVerticies;
    unsigned int numIndecies;
    GLenum shapes;
    std::string name;
    VAO *vao;
public:
    unsigned int getVerticies(){return this->numVerticies;}
    void setVerticies(unsigned int verticies){this->numVerticies = verticies;}

    unsigned int getIndecies(){return this->numIndecies;}
    void setIndecies(unsigned int indecies){this->numIndecies = indecies;}

    GLenum getDrawingType(){return this->shapes;}
    void setDrawingType(GLenum shapes){this->shapes = shapes;}
};


#endif //CLIONTEST_GEOMETRY_H
