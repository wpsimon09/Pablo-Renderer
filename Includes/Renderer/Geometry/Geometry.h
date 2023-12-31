//
// Created by wpsimon09 on 30/12/23.
//

#ifndef CLIONTEST_GEOMETRY_H
#define CLIONTEST_GEOMETRY_H

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
    std::string name;
    VAO *vao;
};


#endif //CLIONTEST_GEOMETRY_H
