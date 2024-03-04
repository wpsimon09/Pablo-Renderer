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
#include "Renderer/Light/IBLPipeline/IBLPipeLine.h"
class Scene {
public:
    Scene();
    inline static std::shared_ptr<SceneNode> root;

    void add(std::unique_ptr<SceneNode> child, std::shared_ptr<SceneNode> parent = root);
    void add(std::unique_ptr<Renderable> renderable, std::shared_ptr<SceneNode> parent= root);

    void update(Shader *shader = NULL);

    void setup();

    void setIblPiepline(const std::shared_ptr<IBLPipeLine>& iblPipeLine){
        this->iblPipeLine = iblPipeLine;
    }

    std::unique_ptr<Camera> camera;
    std::unique_ptr<Light> light;
private:
    std::weak_ptr<IBLPipeLine> iblPipeLine;

};


#endif //PABLO_RENDERER_SCENE_H
