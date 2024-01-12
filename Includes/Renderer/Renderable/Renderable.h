//
// Created by wpsimon09 on 30/12/23.
//

#ifndef CLIONTEST_RENDERABLE_H
#define CLIONTEST_RENDERABLE_H

#include "Renderer/Utils/Vertex/Vertex.h"
#include "vector"
#include "Shader.h"
#include "glm/glm.hpp"
#include "Renderer/Utils/Transformations/Transformations.h"
#include "Texture/Texture.h"
#include "Renderer/Geometry/Geometry.h"
#include "Renderer/Geometry/Shapes/Cube/CubeGeometry.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Material/PBRColor/PBRColor.h"

class Renderable {
private:
    Geometry *objectGeometry;
    Material *objectMaterial;
    glm::mat4 modelMatrix;
public:
    std::string name;

    Renderable(Geometry* geometry, Material * material, std::string name = "renderable");
    Renderable(Shader *shader);

    void render();
    friend std::ostream &operator <<(std::ostream &os, Renderable& obj);

    void setModelMatrix(glm::mat4 modelMatrix){this->modelMatrix = modelMatrix;}

    Shader* getShader();
};


#endif //CLIONTEST_RENDERABLE_H
