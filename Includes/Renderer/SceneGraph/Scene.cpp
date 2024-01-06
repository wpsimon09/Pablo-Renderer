//
// Created by wpsimon09 on 06/01/24.
//

#include "Scene.h"

Scene::Scene() {
    Scene::root = new SceneNode();
}

void Scene::add(SceneNode *child, SceneNode *parent) {
    parent->addChild(child);
}

void Scene::add(Renderable *renderable, SceneNode *parent) {
    parent->addChild(new SceneNode(renderable));
}
