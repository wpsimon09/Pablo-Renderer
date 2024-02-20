//
// Created by wpsimon09 on 04/01/24.
//

#include "SceneNode.h"

SceneNode::SceneNode(std::unique_ptr<Renderable> renderable) {
    this->renderable = std::move(renderable);
    this->parent = nullptr;
    this->transformation = std::make_unique<Transformations>();
}

SceneNode::~SceneNode() {
    if (parent){
        for (int i = children.size() - 1; i >= 0; --i) {
            //delete children[i];
        }
    }
    else delete this;
}

const std::unique_ptr<Renderable> & SceneNode::getRenderable()const {
    return renderable;
}

void SceneNode::setRenderable(std::unique_ptr<Renderable> renderable) {
    this->renderable =std::move(renderable);
}

std::vector<std::unique_ptr<SceneNode>>::const_iterator SceneNode::getChildIteratorStart() {
    return this->children.begin();
}

std::vector<std::unique_ptr<SceneNode>>::const_iterator SceneNode::getChildIteratorEnd() {
    return this->children.end();
}

void SceneNode::addChild(std::unique_ptr<SceneNode> sceneNode) {
    children.push_back(std::move(sceneNode));

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
    if (this->renderable){
        this->renderable->setModelMatrix(this->transformation->getModelMatrix());
    }

    //start recursion
    for (auto & i : children) {
        i->update();
    }
}

void SceneNode::render() {
    if (renderable){
        renderable->render();
    }
}

const std::vector<std::unique_ptr<SceneNode>> & SceneNode::getChildren() const {
    if(!this->children.empty()){
        return this->children;
    }
}


