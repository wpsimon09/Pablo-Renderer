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

    auto iblPipeLine = std::make_shared<IBLPipeLine>("Assets/Textures/HDR/sunrise.hdr");
    iblPipeLine->generateIBLTextures();

    auto cubeGeometry = std::make_shared<CubeGeometry>();
    auto planeGeometry = std::make_shared<PlaneGeometry>();
    auto sphereGeometry = std::make_shared<SphereGeometry>();

    auto gridRenderable = std::make_unique<Grid>();

    auto goldMaterial = std::make_shared<PBRTextured>(true, "/home/wpsimon09/Desktop/Textures/hangar-black", false);

    std::string pabloPath = PABLO_PATH;

    auto pot = std::make_unique<ModelSceneNode>("/home/wpsimon09/Desktop/Models/pot/brass_pot_01_2k.gltf", true);
    pot->transformation->setPosition(-3.0, 1.0f, 0.0f);
    pot->transformation->setScale(9.0f, 5.0f, 9.0f);
    pot->castsShadow(true);

    auto gridSceneNode = std::make_unique<SceneNode>(std::move(gridRenderable));
    gridSceneNode->transformation->setPosition(glm::vec3(0.0f, -0.2f, 0.0f));


    auto color1 = std::make_unique<PBRColor>(glm::vec3(0.8f, 0.0f, 1.0f), true, true);
    auto color2 = std::make_unique<PBRColor>(glm::vec3(0.8f, 1.0f, 1.0f), true, true);

    auto cubeColor = std::make_unique<Renderable>(sphereGeometry, std::move(goldMaterial), "Sphere");

    auto floor = std::make_unique<Renderable>(planeGeometry, std::move(color2), "Floor");
    floor->transformations->setPosition(0.0f, -2.0f, 0.0f);
    floor->transformations->setScale(10.0f, 1.0f, 10.0f);
    floor->recievesShadow = true;
    floor->setBackFaceCull(false);

    const std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    scene->setIblPipeLine(iblPipeLine);

    scene->add(std::move(gridSceneNode));
    scene->add(std::move(floor));
    scene->add(std::move(pot));
    scene->add(std::move(cubeColor));

    pabloRenderer->attachScene(scene);

    pabloRenderer->setDebugTexture(iblPipeLine->iblTextures[3]->type);

    pabloRenderer->render();

    return 0;
}
