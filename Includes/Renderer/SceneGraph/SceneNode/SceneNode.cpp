//
// Created by wpsimon09 on 04/01/24.
//

#include "SceneNode.h"

SceneNode::SceneNode(Renderable *renderable) {
    this->renderable = renderable;
    this->parent = nullptr;
    this->scale = glm::vec3(1.0,1.0,1.0);
    this->worldTransform = glm::mat4(1.0f);
    this->transform = glm::mat4(1.0f);
}

SceneNode::~SceneNode(void) {
    for (unsigned int i = 0;  i<children.size() ; i++) {
        delete this->children[i];
    }
}

Renderable *SceneNode::getRenderable() const {
    return renderable;
}

void SceneNode::setRenderable(Renderable *renderable) {
    SceneNode::renderable = renderable;
}

const glm::mat4 &SceneNode::getTransform() const {
    return transform;
}

void SceneNode::setTransform(const glm::mat4 &transform) {
    SceneNode::transform = transform;
}

const glm::mat4 &SceneNode::getWorldTransform() const {
    return worldTransform;
}

void SceneNode::setWorldTransform(const glm::mat4 &worldTransform) {
    SceneNode::worldTransform = worldTransform;
}

const glm::vec3 &SceneNode::getScale() const {
    return scale;
}

void SceneNode::setScale(const glm::vec3 &scale) {
    SceneNode::scale = scale;
}

std::vector<SceneNode *>::const_iterator SceneNode::getChildIteratorStart() {
    return this->children.begin();
}

std::vector<SceneNode *>::const_iterator SceneNode::getChildIteratorEnd() {
    return this->children.end();
}

void SceneNode::addChild(SceneNode *sceneNode) {
    children.push_back(sceneNode);

    //sets parent of the child to be this
    sceneNode->parent = this;
}

void SceneNode::update() {
    if(parent){

        this->worldTransform = parent->worldTransform * transform;
    }
    else{
        worldTransform = transform;
    }
    for (auto i = children.begin(); i != children.end(); ++i) {
        (*i)->update();
    }
}

void SceneNode::render() {
    if (renderable){renderable->render(); }
}

