//
// Created by wpsimon09 on 30/12/23.
//

#ifndef CLIONTEST_CUBEGEOMETRY_H
#define CLIONTEST_CUBEGEOMETRY_H

#include "Renderer/Geometry/Geometry.h"
#include "cubeVerticies.h"

class CubeGeometry: public Geometry {
public:
    explicit CubeGeometry(std::string name = "CUBE");

protected:
    void generateVAO() override;

    void fillTheVerticies() override;
private:

};


#endif //CLIONTEST_CUBEGEOMETRY_H
