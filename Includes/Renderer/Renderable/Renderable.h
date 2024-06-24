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
    /**
     * @brief Object geometry
     * @see Gemetry.h
     */
    std::shared_ptr<Geometry> objectGeometry;

    /**
     * @brief Material of the object
     * @see Material.h
     */
    std::shared_ptr<Material> objectMaterial;

    /**
     * @brief Model matrix of the renderable
     */
    glm::mat4 modelMatrix;

private:
    /**
     * @brief Backface culling of the renderable default is True
     */
    bool backFaceCulled = true;

public:
    /**
     * @brief Transformation of the renderable, Transformation class contains all the math behind rotation, moving and scaling objects
     * @see Transformations.h
     */
    std::unique_ptr<Transformations> transformations;

    /**
     * @brief Is object casting shadow default value is false
     */
    bool castsShadwo = false;

    /**
     * @brief Does object recieve shadow defatul value is true
     */
    bool recievesShadow = true;

    /**
     * @brief Determines weather renderable is a part of the bigger model or is a simple mesh like cube, sphere etc...
     * It is used for shading and retrieving right texture maps
     * default is false
     */
    bool isModel = false;

    /**
     * @brief Determines weather renderable is displayed using Mesh view. e.g triangles are not filed
     * defatul is false
     */
    bool isLineOnly = false;

    /**
     * @brief Determines if the object is in the scene node structure defaul is false
     */
    bool isPartOfSceneNode = false;

    /**
     * @brief Name of the renderalbe if no name is specified default is "unnamed renderable"
     */
    std::string name = "unnamed renderable";

    /***
     * Creates instance of the Renderable class
     * @param geometry Geometry for renterable to have
     * @param material Material for renderable to hav e
     * @param name name of the renderable default is "rendereable"
     */
    Renderable(std::shared_ptr<Geometry> geometry, std::shared_ptr<Material> material, std::string name = "renderable");

    /***
    * Creates instance of the renderable class
    * @param shader Shader for renderable to use
    */
    explicit Renderable(std::shared_ptr<Shader> shader);

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

    /**
     * @brief Updates the renderable position, model matrix etc...
     */
    void update();

   /**
   * @brief Retrieves renderable material
   * @return material of the renderable
   */
    const std::shared_ptr<Material> getObjectMaterial() const;

    /**
     * @brief Sets the material of the renderable
     * @param material new material of the renderable
     */
    void setMaterial(std::shared_ptr<Material> material) {  this->objectMaterial = material; };

    /**
     * @brief Retrieves geometry of the renderable
     * @return Geometry of the renderable
     */
    std::shared_ptr<Geometry> getRenderableGeometry() { return this->objectGeometry; };

    /**
     * @brief Sets the geometry of the renderable
     * @param geometry new geomtry of the renderable
     */
    void setRenderableGeometry(std::shared_ptr<Geometry> geometry) {this->objectGeometry = geometry;}

    /**
     * @brief Overwritten << operatior for printing the information about the renderable
     * @param os stream of the OS
     * @param obj renderable to pring
     * @return overwritten << operator
     * @deprecated this is depricated and no longer works
     */
    friend std::ostream &operator <<(std::ostream &os, Renderable &obj);

    /**
     * @brief Sets the model matrix of the renderable
     * @param modelMatrix New model matrix
     */
    void setModelMatrix(glm::mat4 modelMatrix) { this->modelMatrix = modelMatrix; }

    /**
     * @brief Gets if the renderable should have backface culling enabled
     * @return ture if renderable should be backface culled false otherwise
     */
    bool getBackFaceCull() { return this->backFaceCulled; }

    /**
     * @brief Sets the backface culling status
     * @param isCulled Backafe cull flag true if should be backface culled false otherwise
     */
    void setBackFaceCull(bool isCulled) { this->backFaceCulled = isCulled; }

    /**
     * @brief Retrieves the shader of the rendrable
     * @return Shader that is used by the material
     */
    std::shared_ptr<Shader> getShader();
};


#endif //CLIONTEST_RENDERABLE_H
