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

/***
 * Class representing renderable object
 * stores material and geometry that will be used for the rendering
 */
class Renderable {
protected:
    std::shared_ptr<Geometry> objectGeometry;
    std::shared_ptr<Material> objectMaterial;
public:
    std::unique_ptr<Transformations> transformations;
    bool castsShadwo = false;
    bool recievesShadow = false;
    bool isModel = false;
    const std::shared_ptr<Material> &getObjectMaterial() const;
    bool isPartOfSceneNode = false;
protected:
    glm::mat4 modelMatrix;
public:
    std::string name = "unnamed renderable";

    /***
     * Creates instance of the Renderable class
     * @param geometry Geometry for renterable to have
     * @param material Material for renderable to hav e
     * @param name name of the renderable default is "rendereable"
     */
    Renderable(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material>  material, std::string name = "renderable");

    /***
    * Creates instance of the renderable class
    * @param shader Shader for renderable to use
    */
    Renderable(std::shared_ptr<Shader> shader);
    Renderable();

    /***
     * Initiates the glDrawElements call and calls configureShader method on the material class
     * Mehtod will draw the renderable to the currently bound GL_FRAMEBUFFER
     */
    virtual void render();

    /***
     * Renders only the geometry of the renderable
     */
    virtual void renderGeomtry();

    std::shared_ptr<Geometry> getRenderableGeometry() {return this->objectGeometry;};

    void update();

    friend std::ostream &operator <<(std::ostream &os, Renderable& obj);

    void setModelMatrix(glm::mat4 modelMatrix)              {this->modelMatrix = modelMatrix;}

    void setMaterial(std::shared_ptr<Material> material)    {this->objectMaterial = material;};

    std::shared_ptr<Shader> getShader();

    ~Renderable()=default;
};


#endif //CLIONTEST_RENDERABLE_H
