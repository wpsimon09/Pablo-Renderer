//
// Created by wpsimon09 on 06/01/24.
//

#ifndef PABLO_RENDERER_SCENE_H
#define PABLO_RENDERER_SCENE_H

#include "Renderer/SceneGraph/SceneNode/SceneNode.h"
#include "camera.h"
#include "Renderer/Renderable/Renderable.h"
#include "Renderer/Light/Light.h"

class Scene {
public:
    Scene();
    inline static SceneNode* root;
    void add(SceneNode* child, SceneNode*parent = root);
    void add(Renderable* renderable, SceneNode *parent= root);
    Camera* camera;
    Light* light;

    Camera *getCamera() const;

    void setCamera(Camera *camera);

    Light *getLight() const;

    void setLight(Light *light);
};


#endif //PABLO_RENDERER_SCENE_H
