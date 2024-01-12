//
// Created by wpsimon09 on 06/01/24.
//

#include "Scene.h"

Scene::Scene() {
    Scene::root = new SceneNode();
    this->camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));
    this->light = new Light(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(10.0f, 10.0f, 10.0f));
}

void Scene::add(SceneNode *child, SceneNode *parent) {
    parent->addChild(child);
}

void Scene::add(Renderable *renderable, SceneNode *parent) {
    parent->addChild(new SceneNode(renderable));
}

Camera *Scene::getCamera() const {
    return camera;
}

void Scene::setCamera(Camera *camera) {
    Scene::camera = camera;
}

Light *Scene::getLight() const {
    return light;
}

void Scene::setLight(Light *light) {
    Scene::light = light;
}

void Scene::render(SceneNode *node) {
    if (node->getRenderable()){
        node->render();
    }
    for (std::vector<SceneNode*>::const_iterator i = node->getChildIteratorStart(); i<node->getChildIteratorEnd(); ++i) {
        this->render(*i);
    }
}

void Scene::update(Shader *shader) {
    std::cout<<root->getNumberOfChildren();
    Scene::root->update();
}


void Scene::setup() {

}

