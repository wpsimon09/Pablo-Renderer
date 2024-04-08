//
// Created by wpsimon09 on 04/01/24.
//

#include "SceneNode.h"

SceneNode::SceneNode(std::unique_ptr<Renderable> renderable) {
    this->renderable = std::move(renderable);
    if(this->renderable != nullptr && this->renderable->transformations != nullptr){
        this->transformation = std::move(this->renderable->transformations);
    }
    else{
        this->transformation = std::make_unique<Transformations>();
    }

    this->parent = nullptr;
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

const std::vector<std::unique_ptr<SceneNode>> & SceneNode::getChildren() const {
    return this->children;
}

void SceneNode::render(RENDERING_CONSTRAINS renderingConstrain,bool geometryOnly) {
    if (renderable){
        if(renderingConstrain == NONE){
            renderable->render();
        }
        else if (renderingConstrain == SHADOW_ONLY && renderable->castsShadwo && geometryOnly){
            renderable->renderGeomtry();
        }
    }
}



