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
#include "Renderer/Material/PBRTexture/PBRTextured.h"
#include "Renderer/Geometry/Shapes/Custom/ModelGeometry.h"

class Renderable {
protected:
    std::unique_ptr<Geometry> objectGeometry;
    std::unique_ptr<Material> objectMaterial;
    glm::mat4 modelMatrix;
public:
    std::string name;

    Renderable(std::unique_ptr<Geometry> geometry, std::unique_ptr<Material>  material, std::string name = "renderable");
    Renderable(std::unique_ptr<Shader> shader);
    Renderable();

    virtual void render();
    friend std::ostream &operator <<(std::ostream &os, Renderable& obj);

    void setModelMatrix(glm::mat4 modelMatrix){this->modelMatrix = modelMatrix;}

    std::unique_ptr<Shader> getShader();
};


#endif //CLIONTEST_RENDERABLE_H
