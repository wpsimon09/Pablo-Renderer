//
// Created by wpsimon09 on 30/12/23.
//

#ifndef CLIONTEST_GEOMETRY_H
#define CLIONTEST_GEOMETRY_H

#include "glad/glad.h"
#include "vector"
#include "Renderer/Utils/Vertex/Vertex.h"
#include "Renderer/Utils/VAO/VAO.h"
#include "memory"

class Geometry {
public:
    GLuint getVertexArrays() const ;
    void bindVertexArrays() const;
    void unbindVertexArrays() const;
    std::string getName() const;
    virtual ~Geometry(){};
    virtual void render() const;
    unsigned int numVerticies;
    unsigned int numIndecies;
protected:
    GLenum shapes;
    std::string name;
    std::unique_ptr<VAO> vao;
public:
};


#endif //CLIONTEST_GEOMETRY_H
