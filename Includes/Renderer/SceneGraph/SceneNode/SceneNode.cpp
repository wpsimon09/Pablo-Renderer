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

    this->initialPosition = this->transformation->getPosition();
    this->initialRotation = this->transformation->getRotations();
    this->initialScale = this->transformation->getScale();

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
    this->isParent = true;

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
    if(this->isVisible){
        if (renderable){
            if(renderingConstrain == NONE){
                renderable->render();
            }
            else if (renderingConstrain == SHADOW_ONLY && renderable->castsShadwo && geometryOnly){
                renderable->renderGeomtry();
            }
        }
    }
}

void SceneNode::renderUI() {
    if(renderable != nullptr){
        if(ImGui::TreeNodeEx(this->renderable->name.c_str())){
            if(ImGui::TreeNodeEx("Position")){

                ImGui::SliderFloat("X", &this->transformation->getPosition_UI().x, -10.0f, 10.0f);
                ImGui::SliderFloat("Y", &this->transformation->getPosition_UI().y, -10.0f, 10.0f);
                ImGui::SliderFloat("Z", &this->transformation->getPosition_UI().z, -10.0f, 10.0f);

                if(ImGui::Button("Reset")){
                    this->transformation->setPosition(this->initialPosition);
                }

                ImGui::TreePop();
            }

            if(ImGui::TreeNodeEx("Rotation")){

                ImGui::SliderFloat("X", &this->transformation->getRotation_UI().x, 0.0f, 360.0f);
                ImGui::SliderFloat("Y", &this->transformation->getRotation_UI().y, 0.0f, 360.0f);
                ImGui::SliderFloat("Z", &this->transformation->getRotation_UI().z, 0.0f, 360.0f);

                if(ImGui::Button("Reset")){
                    this->transformation->setRotations(this->initialRotation);
                }

                ImGui::TreePop();
            }

            if(ImGui::TreeNodeEx("Scale")){

                ImGui::SliderFloat("X", &this->transformation->getScale_UI().x,0.0f, 100.0f);
                ImGui::SliderFloat("Y", &this->transformation->getScale_UI().y,0.0f, 100.0f);
                ImGui::SliderFloat("Z", &this->transformation->getScale_UI().z,0.0f, 100.0f);


                if(ImGui::Button("Reset")){
                    this->transformation->setScale(this->initialScale);
                }

                ImGui::TreePop();
            }
            ImGui::Checkbox("Is visible", &this->isVisible);

            if(ImGui::Button("Reset all")){
                this->transformation->setScale(this->initialScale);
                this->transformation->setRotations(this->initialRotation);
                this->transformation->setScale(this->initialScale);
            }
            ImGui::TreePop();
        }
    }
}



