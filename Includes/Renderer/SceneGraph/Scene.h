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
#include "Renderer/Utils/RenderingConstrains/RenderingConstrains.h"
#include "Renderer/Utils/Camera/OrbitCamera/OrbitCamera.h"
#include "Renderer/Light/DirectionLight/DirectionalLight.h"
#include "Renderer/Light/AreaLight/AreaLight.h"
#include "Renderer/Enums/LightTypes.h"
#include "Renderer/Utils/SkyBox/SkyBox.h"
#include "map"


/***
 * Class that holds every information about what should be render and where in the world space
 * Is responsible for updating state of the stored renderables and scene nodes
 */
class Scene {
public:
    /***
     * Creates empty Scene class
     */
    Scene();

    /***
     * Root node of the scene node structure
     */
    inline static std::shared_ptr<SceneNode> root;

    /***
     * Adds new scene node to the parent
     * @param child scene node to add
     * @param parent parent to which the provided child belongs to default is root
     */
    void add(std::unique_ptr<SceneNode> child, std::shared_ptr<SceneNode> parent = root);

    /***
     * Adds renderable to the provided parent by creating new scene node
     * @param renderable renderable object
     * @param parent parent to which the provided child belongs to default is root
     */
    void add(std::unique_ptr<Renderable> renderable, std::shared_ptr<SceneNode> parent = root);

    SkyBox& getSkyBox() {return *this->skyBox;}

    void removeSceneNode(int id);

    /***
     * Updates the scene node structure
     */
    void update();

    /***
     * Setups all of the properties of the scene
     */
    void setup();

    float getIDofSelectedSceneNode() {return this->selectedNodeID;}

    std::map<LIGHT_TYPE, std::unique_ptr<Light>> lights;

    std::unique_ptr<OrbitCamera> camera;
    std::unique_ptr<Light> light;
private:
    std::shared_ptr<IBLPipeLine> iblPipeLine;
    float selectedNodeID = -1;
    std::unique_ptr<SkyBox> skyBox;
public:
    const std::shared_ptr<IBLPipeLine> &getIblPipeLine() const;
    RENDERING_CONSTRAINS renderingConstrains = NONE;
    void setIblPipeLine(const std::shared_ptr<IBLPipeLine> &iblPipeLine);
};


#endif //PABLO_RENDERER_SCENE_H
