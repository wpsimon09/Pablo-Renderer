//
// Created by wpsimon09 on 04/01/24.
//

#include "SceneNode.h"

SceneNode::SceneNode(Renderable *renderable) {
    this->renderable = renderable;
    this->parent = nullptr;
    this->transformation = new Transformations();
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
        this->transformation->computeModelMatrix(parent->transformation->getModelMatrix());
    }
    else {
        this->transformation->computeModelMatrix();
    }

    for (auto & i : children) {
        i->update();
    }
}

void SceneNode::render() {
    if (renderable){
        renderable->render();
    }
}


