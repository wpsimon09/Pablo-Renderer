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

class GeometryID {
public:
 static inline int ID;
};

/***
 * Represents geometrical information about object
 */
class Geometry {
public:
    Geometry() {this->ID = GeometryID::ID++;}

    /**
     *
     * @return returns index of the vertex of the geometry
     */
    GLuint getVertexArrays() const ;

    /**
     * Binds the vertex array ID of the class to the GL_VERTEX_ARRAY target
     */
    void bindVertexArrays() const;

    /***
     * Binds to the default GL_VERTEX_ARRAY target which is 0
     */
    void unbindVertexArrays() const;

    /***
     * Renders the geometry based on the contents of the class properties to the currently bound GL_FRAME_BUFFER
     */
    virtual void render() const;

    /***
     * Gets the edges of the shape for area light
     * @return edges of the geometry as vector of glm::vec3 positions
     */
    virtual std::vector<glm::vec3>getAreaLightCornerPoints();

    unsigned int getID() {return ID;};

    std::string getName() const;

    virtual ~Geometry(){};
    unsigned int numVerticies;
    unsigned int numIndecies;

    friend bool operator==(const Geometry &lhs, const Geometry &rhs) {
     return lhs.ID == rhs.ID;
    }

    friend bool operator!=(const Geometry &lhs, const Geometry &rhs) {
     return !(lhs == rhs);
    }

   protected:
    unsigned int ID;

    /***
     * How to render the geometry: GL_TRIANGLES, GL_LINES, GL_TRIANGLE_STRIP etc...
     */
    GLenum shapes;

    /***
     * Unique pointer to the Vertex array class
     */
    std::unique_ptr<VAO> vao;

    /**
     * @brief Name of the geometry
     */
    std::string name;
};


#endif //CLIONTEST_GEOMETRY_H
