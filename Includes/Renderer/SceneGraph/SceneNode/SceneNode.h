//
// Created by wpsimon09 on 04/01/24.
//

#ifndef PABLO_RENDERER_SCENENODE_H
#define PABLO_RENDERER_SCENENODE_H

#include "Renderer/Utils/Transformations/Transformations.h"
#include "Renderer/Renderable/Renderable.h"
#include "Renderer/Utils/RenderingConstrains/RenderingConstrains.h"
#include "imgui.h"
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

public:

    std::unique_ptr<Transformations> transformation;

    const std::unique_ptr<Renderable> &getRenderable() const;

    void setRenderable(std::unique_ptr<Renderable> renderable);

    /***
     * Adds child to self
     * @param sceneNode child to be added
     */
    void addChild(std::unique_ptr<SceneNode> sceneNode);


    void renderUI();

    /***
     * Updates self and child's positions and other parameters
     */
    void update();

    /***
     * Renders self and all the children to the currently bound GL_FRAMEBUFFER
     */
    void render(RENDERING_CONSTRAINS renderingConstrain, bool geometryOnly = false);

    /***
     * Getter for children
     * @return reference to the all children owned by the scene node
     */
    const std::vector<std::unique_ptr<SceneNode>> &getChildren() const;

    std::vector<std::unique_ptr<SceneNode>>::const_iterator getChildIteratorStart();

    std::vector<std::unique_ptr<SceneNode>>::const_iterator getChildIteratorEnd();

    //facade
    glm::vec3 getPosition() const { return this->transformation->getPosition(); }

    const glm::vec3 getRotations() const { return this->transformation->getRotations(); }

    const glm::vec3 getScale() const { return this->transformation->getScale(); }

    const glm::mat4 getModelMatrix() const { return this->transformation->getModelMatrix(); }

    const unsigned long getNumberOfChildren() const { return this->children.size(); }

protected:
    SceneNode *parent;

    bool isVisible = true;

    bool isParent = false;

    glm::vec3 initialPosition;
    glm::vec3 initialRotation;
    glm::vec3 initialScale;

    std::unique_ptr<Renderable> renderable;

    /***
     * Children owned by the scene node
     */
    std::vector<std::unique_ptr<SceneNode>> children;
};


#endif //PABLO_RENDERER_SCENENODE_H
