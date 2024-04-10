//
// Created by wpsimon09 on 15/03/24.
//

#ifndef PABLO_RENDERER_SPHEREGEOMETRY_H
#define PABLO_RENDERER_SPHEREGEOMETRY_H

#include "Renderer/Geometry/Geometry.h"
#include "vector"
class SphereGeometry: public Geometry {
public:

    /***
     * Crates instance of the sphere geometry
     * @param name @def sphere
     * @param quality represents how sharp the sphere appears to be @def 64
     */
    explicit SphereGeometry(std::string name = "SPHERE", unsigned int quality = 64);

    /***
     * Renders the sphere to the currently bound GL_FRAMEBUFFER
     */
    void render() const override;
private:
    static std::unique_ptr<VAO> generateSpeher(unsigned int quality);
};


#endif //PABLO_RENDERER_SPHEREGEOMETRY_H
