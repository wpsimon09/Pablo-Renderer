//
// Created by wpsimon09 on 04/01/24.
//

#ifndef PABLO_RENDERER_SCENENODE_H
#define PABLO_RENDERER_SCENENODE_H

#include "Renderer/Utils/Transformations/Transformations.h"
#include "Renderer/Renderable/Renderable.h"
#include "Renderer/Utils/RenderingConstrains/RenderingConstrains.h"
#include "imgui.h"

class ID {
public:
    static inline float id = 0;
};

/***
 * Scene graph pattern implementation
 */
class SceneNode {
public:
    /***
     * Creates a new scene node
     * @param renderable renderable which scene node posses
     */
    explicit SceneNode(std::unique_ptr<Renderable> renderable = nullptr);

    ~SceneNode();

    const std::unique_ptr<Renderable> &getRenderable() const;

    /**
     * @brief Changes the renderable of the scene node
     * @param renderable Renderable to be used in SceneNode
     */
    void setRenderable(std::unique_ptr<Renderable> renderable);

    /***
     * Adds child to self
     * @param sceneNode child to be added
     */
    void addChild(std::unique_ptr<SceneNode> sceneNode);


    /***
     * Updates self and child's positions and other parameters
     */
    void update();

    /***
     * Renders self and all the children to the currently bound GL_FRAMEBUFFER, using their proper material and shading
     */
    void render(RENDERING_CONSTRAINS renderingConstrain, bool geometryOnly = false);

    /**
     * @brief Renders self and children using only glDrawCall without specifing material properties,
     * so before this mehtod is called the shader should be configured to handle rendering of the geometry
     */
    void renderGeometry();

    /***
     * Getter for children
     * @return reference to the all children owned by the scene node
     */
    const std::vector<std::unique_ptr<SceneNode> > &getChildren() const;

    /**
     * @brief Getter for childre itteratior
     * @return First child to be used as an itterator
     */
    std::vector<std::unique_ptr<SceneNode> >::const_iterator getChildIteratorStart();

    /**
     * @brief End of the children
     * @return End of the child vector to be used as an itterator
     */
    std::vector<std::unique_ptr<SceneNode> >::const_iterator getChildIteratorEnd();

    /**
     * @brief Chnages materail of the attached renderable
     * @param newMaterial Material that will be applied to the renderable if there is any
     */
    void setMaterial(std::shared_ptr<Material> newMaterial);

    /**
     * @brief Retrieves the ability of the scene node to be rendered (bit missleading name tho)
     * @return True if the object is visible false otherwise(not from camera point of view) this means that this flag determines if the renderable can be rendered
     */
    bool &getVisibility() { return isVisible; }

    /**
     * @brief Retrieves ID of the scene node
     * @return Unique ID of the scene node
     */
    float getID() { return this->id; }


    /*
     **********************************
     | FACADE FOR THE TRANSFORMATIONS |
     **********************************
     */
    glm::vec3 getPosition() const { return this->transformation->getPosition(); }

    const glm::vec3 getRotations() const { return this->transformation->getRotations(); }

    const glm::vec3 getScale() const { return this->transformation->getScale(); }

    const glm::mat4 getModelMatrix() const { return this->transformation->getModelMatrix(); }

    const unsigned long getNumberOfChildren() const { return this->children.size(); }

    glm::vec3 getInitialPosition() { return initialPosition; }
    glm::vec3 getInitialRotation() { return initialRotation; }
    glm::vec3 getInitialScale() { return initialScale; }
    /*
    ********************************************************************************************
    ********************************************************************************************
    */

    /**
     * @brief Determines if the SceneNode is currently selected
     */
    bool isSelected = false;

    /**
     * @brief Transformation of the scnee node @class Transformations
     */
    std::unique_ptr<Transformations> transformation;

protected:
    /**
     * @brief Unique ID of the scene node
     */
    float id;

    /**
     * @brief Parent of the scene node
     * @todo memory leak ?
     */
    SceneNode *parent;
    /**
     * @brief Is scene node visible or rather if it can be rendereed defautl = True
     */
    bool isVisible = true;
    /**
     * @brief is scene node parrent node if true has at least 1 child defautl false
     */
    bool isParent = false;

    /**
     * @brief Renderable of the SceneNode @class Renderable
     */
    std::unique_ptr<Renderable> renderable;

    /***
     * Children owned by the scene node
     */
    std::vector<std::unique_ptr<SceneNode> > children;

    /*
     ********************************
     * POSITIONS BEFORE TRANSLATIONS |
     *********************************
    */
    glm::vec3 initialPosition;
    glm::vec3 initialRotation;
    glm::vec3 initialScale;
};


#endif //PABLO_RENDERER_SCENENODE_H
