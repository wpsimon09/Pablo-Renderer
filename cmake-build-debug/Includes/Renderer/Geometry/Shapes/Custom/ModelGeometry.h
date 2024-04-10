//
// Created by wpsimon09 on 31/12/23.
//

#ifndef MODELGEOMETRY_H
#define MODELGEOMETRY_H

#include "Renderer/Geometry/Geometry.h"
#include "vector"

/***
 * Represents geometry of the more complicated mesh structure
 */
class ModelGeometry : public Geometry {
public:

    /***
     * Creates an instance of the ModelGeometry class
     * @param name name of the mesh
     * @param verticies verticies of the mesh
     * @param indecies indecies of the mesh
     */
    explicit ModelGeometry(std::string name, std::vector<Vertex> verticies, std::vector<unsigned int> indecies = {0});

    /***
     * Renders the mesh to the currently bound GL_FRAMEBUFFER
     */
    void render() const override;

private:
};

#endif //PABLO_RENDERER_MODELGEOMETRY_H
