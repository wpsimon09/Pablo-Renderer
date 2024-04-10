//
// Created by wpsimon09 on 30/12/23.
//

#ifndef CLIONTEST_CUBEGEOMETRY_H
#define CLIONTEST_CUBEGEOMETRY_H

#include "Renderer/Geometry/Geometry.h"

/***
 * Class representing cube geometry
 */
class CubeGeometry: public Geometry {
public:

    /***
     * Creates instance of the cube geomtry
     * @param name name of the instance default is "CUBE"
     */
    explicit CubeGeometry(std::string name = "CUBE");
private:

};


#endif //CLIONTEST_CUBEGEOMETRY_H
