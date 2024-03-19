//
// Created by wpsimon09 on 04/01/24.
//

#include "SceneNode.h"

SceneNode::SceneNode(std::unique_ptr<Renderable> renderable, std::unique_ptr<Transformations> transformations ) {
    this->renderable = std::move(renderable);
    if(renderable != nullptr){
        if(!renderable->isPartOfSceneNode){
            this->renderable->isPartOfSceneNode = true;
            this->transformation = std::move(this->renderable->transformations);
        }
    }

    this->parent = nullptr;
    this->transformation = std::make_unique<Transformations>();
}

SceneNode::~SceneNode()=default;

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
    sceneNode->parent = this;

    children.push_back(std::move(sceneNode));
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
    return this->children;
}



