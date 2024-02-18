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
    inline static std::unique_ptr<SceneNode> root;

    void add(std::unique_ptr<SceneNode> child, std::unique_ptr<SceneNode> parent = std::move(root));
    void add(std::unique_ptr<Renderable> renderable, std::unique_ptr<SceneNode> parent= std::move(root));

    void update(Shader *shader = NULL);

    void setup();

    std::unique_ptr<Camera> camera;
    std::unique_ptr<Light> light;

};


#endif //PABLO_RENDERER_SCENE_H
