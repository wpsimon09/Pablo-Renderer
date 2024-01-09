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

    const glm::mat4 &getTransform() const;
    void setTransform(const glm::mat4 &transform);

    const glm::mat4 &getWorldTransform() const;
    void setWorldTransform(const glm::mat4 &worldTransform);

    const glm::vec3 &getScale() const;

    void setScale(const glm::vec3 &scale);
    void addChild(SceneNode* sceneNode);
    void update();
    void render();

    std::vector<SceneNode*>::const_iterator getChildIteratorStart();
    std::vector<SceneNode*>::const_iterator getChildIteratorEnd();

protected:
    Renderable* renderable;
    SceneNode* parent;

    //local transformations
    glm::mat4 transform;

    //model matrix
    glm::mat4 worldTransform;
    glm::vec3 scale;
    std::vector<SceneNode*> children;
};


#endif //PABLO_RENDERER_SCENENODE_H
