//
// Created by wpsimon09 on 04/01/24.
//

#ifndef PABLO_RENDERER_SCENENODE_H
#define PABLO_RENDERER_SCENENODE_H

#include "Renderer/Renderable/Renderable.h"
#include "Renderer/Utils/Transformations/Transformations.h"

class SceneNode {
public:
    SceneNode(Renderable* renderable = NULL);
    ~SceneNode(void);
public:

    Renderable *getRenderable() const;
    void setRenderable(Renderable *renderable);

    //facade
    void setPositions(glm::vec3 position)   {this->transformation->setPosition(position);}
    const glm::vec3 getPosition() const {return this->transformation->getPosition();}

    void setRotations(glm::vec3 rotationsEurel) {this->transformation->setRotations(rotationsEurel);}
    const glm::vec3 getRotations() const {return this->transformation->getRotations(); }

    void setScale(glm::vec3 scale) {this->transformation->setScale(scale);}
    const glm::vec3 getScale() const {return this->transformation->getScale();}

    const glm::mat4 getModelMatrix() const {return this->transformation->getModelMatrix();}

    void addChild(SceneNode* sceneNode);
    void update();
    void render();

    std::vector<SceneNode*>::const_iterator getChildIteratorStart();
    std::vector<SceneNode*>::const_iterator getChildIteratorEnd();

protected:
    Renderable* renderable;
    SceneNode* parent;

    Transformations *transformation;
    std::vector<SceneNode*> children;
};


#endif //PABLO_RENDERER_SCENENODE_H
