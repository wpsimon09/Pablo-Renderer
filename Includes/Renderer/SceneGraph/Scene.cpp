//
// Created by wpsimon09 on 06/01/24.
//

#include "Scene.h"

Scene::Scene() {
    Scene::root = std::make_unique<SceneNode>();
    this->camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));
    this->light = std::make_unique<Light>(glm::vec3(0.0f, 3.0f, 3.0f), glm::vec3(5.0f, 5.0f, 4.2f));
    Scene::root->addChild(std::move(this->light->lightSceneNode));
}


void Scene::update(Shader *shader) {
    Scene::root->update();
}

void Scene::setup() {
    auto floor = std::make_unique<Floor>();
    floor->setScale(glm::vec3(5.0f, 1.0f, 5.0f));
    this->add(std::move(floor));
}

void Scene::add(std::unique_ptr<Renderable> renderable, std::unique_ptr<SceneNode> parent) {
    parent->addChild(std::make_unique<SceneNode>(std::move(renderable)));
}

void Scene::add(std::unique_ptr<SceneNode> child, std::unique_ptr<SceneNode> parent) {
    parent->addChild(std::move(child));
}


