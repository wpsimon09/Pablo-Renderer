//
// Created by wpsimon09 on 06/01/24.
//

#ifndef PABLO_RENDERER_SCENE_H
#define PABLO_RENDERER_SCENE_H

#include "camera.h"
#include "Renderer/Renderable/Renderable.h"
#include "Renderer/Light/Light.h"
#include "SceneNode/SceneNode.h"
#include "Renderer/SceneGraph/Floor/Floor.h"
#include "Renderer/Renderable/Grid/Grid.h"

class Scene {
public:
    Scene();
    inline static SceneNode* root;

    void add(SceneNode* child, SceneNode *parent = root);
    void add(Renderable* renderable, SceneNode *parent= root);

    void update(Shader *shader = NULL);

    void setup();

    Camera* camera;
    Light* light;

};


#endif //PABLO_RENDERER_SCENE_H
