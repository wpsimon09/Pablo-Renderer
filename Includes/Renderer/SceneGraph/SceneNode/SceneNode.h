//
// Created by wpsimon09 on 04/01/24.
//

#ifndef PABLO_RENDERER_SCENENODE_H
#define PABLO_RENDERER_SCENENODE_H

#include "Renderer/Utils/Transformations/Transformations.h"
#include "Renderer/Renderable/Renderable.h"

class SceneNode {
public:
    SceneNode(std::unique_ptr<Renderable> renderable = NULL);
    ~SceneNode();
public:

    const std::unique_ptr<Renderable> & getRenderable() const ;
    void setRenderable(std::unique_ptr<Renderable> renderable);

    void addChild(std::unique_ptr<SceneNode> sceneNode);
    void update();
    void render();

    const std::vector<std::unique_ptr<SceneNode>> & getChildren() const;

    std::vector<std::unique_ptr<SceneNode>>::const_iterator getChildIteratorStart();
    std::vector<std::unique_ptr<SceneNode>>::const_iterator getChildIteratorEnd();

    //facade
    void setPositions(glm::vec3 position)   {this->transformation->setPosition(position);}
    glm::vec3 getPosition() const {return this->transformation->getPosition();}

    void setRotations(glm::vec3 rotationsEurel) {this->transformation->setRotations(rotationsEurel);}
    const glm::vec3 getRotations() const {return this->transformation->getRotations(); }

    void setScale(glm::vec3 scale) {this->transformation->setScale(scale);}
    const glm::vec3 getScale() const {return this->transformation->getScale();}

    const glm::mat4 getModelMatrix() const {return this->transformation->getModelMatrix();}

    const unsigned long getNumberOfChildren() const{return this->children.size();}

protected:
    SceneNode* parent;
    std::unique_ptr<Renderable> renderable;

    std::unique_ptr<Transformations> transformation;
    std::vector<std::unique_ptr<SceneNode>> children;
};


#endif //PABLO_RENDERER_SCENENODE_H
