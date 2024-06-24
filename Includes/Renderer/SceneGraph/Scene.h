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

    SkyBox &getSkyBox() { return *this->skyBox; }

    void removeSceneNode(int id);

    /***
     * Updates the scene node structure
     */
    void update();

    /***
     * Setups all of the properties of the scene
     */
    void setup();

    /**
     * @brief Sets the ID of the selected node to be used by the UI
     * @param id id of the selected scene node picked from the screen
     */
    void setSelectedNodeID(float id) { selectedNodeID = id; }

    /**
     * @brief Retrieves the node that is being selected by UI or by pixel picking
     */
    float getSelectedNodeID() { return selectedNodeID; }

    /**
     * @brief Retrieves the IBL pipeline of the scene
     * @return reference to IBL pipeline
     */
    const std::shared_ptr<IBLPipeLine> &getIblPipeLine() const;

    /**
     * @brief Sets the different IBL pipeline to be used
     * @param iblPipeLine ibl pipeline to be used
     */
    void setIblPipeLine(const std::shared_ptr<IBLPipeLine> &iblPipeLine);

    /**
     * @brief Map of the lights in the scene (key : LIGHT_TYPE, value : @class Light)
     */
    std::map<LIGHT_TYPE, std::unique_ptr<Light> > lights;

    /**
     * @brief Camera to be used by the scene
     */
    std::unique_ptr<OrbitCamera> camera;

    /**
     * @brief Light used by the scene
     * @deprecated replaced by lights map
     */
    std::unique_ptr<Light> light;

    /**
     * @brief Rendering constarins of the scene, for example to only render objects that casts shadows
     */
    RENDERING_CONSTRAINS renderingConstrains = NONE;

private:
    /**
     * @brief IBL pipeline utilized by the scene
     */
    std::shared_ptr<IBLPipeLine> iblPipeLine;

    /**
     * @brief Scene node ID that is currently selected
     */
    float selectedNodeID = -1;

    /**
     * @brief Sky box of the scene
     */
    std::unique_ptr<SkyBox> skyBox;
};


#endif //PABLO_RENDERER_SCENE_H
