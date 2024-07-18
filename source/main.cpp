#include<glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "stb_image.h"
#include "Renderer/Geometry/Shapes/Cube/CubeGeometry.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Renderable/Renderable.h"
#include "Renderer/SceneGraph/Scene.h"
#include "Renderer/Material/PBRTexture/PBRTextured.h"
#include "Renderer/SceneGraph/ModelSceneNode/ModelSceneNode.h"
#include "Renderer/PabloRenderer.h"
#include "Renderer/Material/SkyBoxMaterial/SkyBoxMaterial.h"
#include "Renderer/Light/IBLPipeline/IBLPipeLine.h"
#include "Renderer/Geometry/Shapes/Sphere/SphereGeometry.h"


//screen coordinates
int SCR_WIDTH = 1920;
int SCR_HEIGHT = 1080;


int main() {
    auto pabloRenderer = PabloRenderer::getInstance();
    pabloRenderer->init();

    auto iblPipeLine = std::make_shared<IBLPipeLine>("Assets/Textures/HDR/sunset.hdr");
    iblPipeLine->generateIBLTextures();

    auto cubeGeometry = std::make_shared<CubeGeometry>();
    auto planeGeometry = std::make_shared<PlaneGeometry>();
    auto sphereGeometry = std::make_shared<SphereGeometry>();

    auto assetsManager = AssetsManager::getInstance();

    auto gridRenderable = std::make_unique<Grid>();

    auto goldMaterial = std::make_shared<PBRTextured>(true, "/home/wpsimon09/Desktop/Textures/wood", false);
    assetsManager->storeMaterial(goldMaterial);

    std::string pabloPath = PABLO_PATH;

    auto pot = std::make_unique<ModelSceneNode>("/home/wpsimon09/Desktop/Models/marble_bust_01_2k.gltf/marble_bust_01_2k.gltf", true);
    pot->transformation->setPosition(40.0, 0.0f, 30.0f);
    pot->transformation->setScale(60.0f, 60.0f, 60.0f);
    pot->castsShadow(true);



    auto gridSceneNode = std::make_unique<SceneNode>(std::move(gridRenderable));
    gridSceneNode->transformation->setPosition(glm::vec3(0.0f, -1.2f, 0.0f));

    auto color1 = std::make_shared<PBRColor>(glm::vec3(0.8f, 0.0f, 1.0f), false, true);
    assetsManager->storeMaterial(color1);

    auto color2 = std::make_shared<PBRColor>(glm::vec3(0.8f, 1.0f, 1.0f), false, true);
    assetsManager->storeMaterial(color2);

    auto color3 = std::make_shared<PBRColor>(glm::vec3(0.0f, 0.6f, 0.0f), false, true);
    assetsManager->storeMaterial(color2);

    auto cubeColor = std::make_unique<Renderable>(cubeGeometry, color2, "Cube");
    cubeColor->transformations->setPosition(0.0f, 10.0f, 30.0f);
    cubeColor->transformations->setScale(10.0F,10.0f, 10.0f);

    auto planeToReflect = std::make_unique<Renderable>(planeGeometry, goldMaterial, "Plane");
    planeToReflect->transformations->setScale(90.0f, 90.0f, 90.0f);
    planeToReflect->transformations->setRotations(90.0f, 180.0f, 0.0F);
    planeToReflect->transformations->setPosition(0.0f ,40.0f, -70.0f);
    planeToReflect->setBackFaceCull(false);

    auto floor = std::make_unique<Renderable>(planeGeometry, color1, "Floor");
    floor->transformations->setPosition(0.2f, 0.0f, 50.0f);
    floor->transformations->setScale(90.0f, 1.0f, 90.0f);
    floor->recievesShadow = true;

    floor->setBackFaceCull(false);

    auto sphere = std::make_unique<Renderable>(sphereGeometry, color3, "sphere");
    sphere->transformations->setScale(10.0F,10.0f, 10.0f);
    sphere->transformations->setPosition(-30.0f, 10.0f, 30.0f);
    sphere->castsShadwo = true;

    const std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    scene->setIblPipeLine(iblPipeLine);

    scene->add(std::move(gridSceneNode));
    scene->add(std::move(floor));
    scene->add(std::move(pot));
    scene->add(std::move(planeToReflect));
    scene->add(std::move(cubeColor));
    scene->add(std::move(sphere));
    pabloRenderer->attachScene(scene);

    pabloRenderer->setDebugTexture(iblPipeLine->iblTextures[3]->type);

    pabloRenderer->render();

    return 0;
}
