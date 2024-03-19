//
// Created by wpsimon09 on 06/01/24.
//

#include "Scene.h"

Scene::Scene() {
    Scene::root = std::make_shared<SceneNode>();
    this->camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    this->light = std::make_unique<Light>(glm::vec3(0.0f, 3.0f, 3.0f), glm::vec3(20.0f, 20.0f, 20.2f));
}


void Scene::update() {
    Scene::root->update();
}

void Scene::setup() {
}

void Scene::add(std::unique_ptr<Renderable> renderable, std::shared_ptr<SceneNode> parent) {
    if(!renderable->isPartOfSceneNode){
        auto newSceneNode = std::make_unique<SceneNode>(std::move(renderable));
    }
    parent->addChild(std::make_unique<SceneNode>(std::move(renderable)));
}

void Scene::add(std::unique_ptr<SceneNode> child, std::shared_ptr<SceneNode> parent) {
    parent->addChild(std::move(child));
}

const std::shared_ptr<IBLPipeLine> &Scene::getIblPipeLine() const {
    return iblPipeLine;
}

void Scene::setIblPipeLine(const std::shared_ptr<IBLPipeLine> &iblPipeLine) {
    Scene::iblPipeLine = iblPipeLine;
}
