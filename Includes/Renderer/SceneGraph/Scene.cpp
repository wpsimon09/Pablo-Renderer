//
// Created by wpsimon09 on 06/01/24.
//

#include "Scene.h"

Scene::Scene() {
    Scene::root = new SceneNode();
    this->camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    this->light = new Light(glm::vec3(0.0f, 3.0f, 3.0f), glm::vec3(5.0f, 5.0f, 4.2f));
    Scene::root->addChild(this->light->lightIcon);
}

void Scene::add(SceneNode *child, SceneNode *parent) {
    parent->addChild(child);
}

void Scene::add(Renderable *renderable, SceneNode *parent) {
    parent->addChild(new SceneNode(renderable));
}

void Scene::update(Shader *shader) {
    Scene::root->update();
}

void Scene::setup() {
    auto floor = new Floor();
    floor->setScale(glm::vec3(5.0f, 1.0f, 5.0f));
    this->add(floor);

    this->add(&grid);
}


