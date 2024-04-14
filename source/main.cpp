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

    auto PBRShader = std::make_shared<Shader>("VertexShader/PBR/PBRVertex-Simple.glsl", "FragmentShader/PBR/PBRFragmentTextures.glsl", "PBR shader");
    auto PBRColorShader = std::make_shared<Shader>("VertexShader/PBR/PBRVertex-Simple.glsl", "FragmentShader/PBR/PBRFragment.glsl", "PBR shader2");

    auto iblPipeLine = std::make_shared<IBLPipeLine>("Assets/Textures/HDR/hill.hdr");
    iblPipeLine->generateIBLTextures();

    auto cubeGeometry = std::make_shared<CubeGeometry>();
    auto planeGeometry = std::make_shared<PlaneGeometry>();
    auto sphereGeometry = std::make_shared<SphereGeometry>();

    auto skyBox = std::make_unique<SkyBoxMaterial>(*iblPipeLine->envMap, "enviromentMap");

    //create renderable object
    auto skyboxCube = std::make_unique<Renderable>(cubeGeometry, std::move(skyBox));

    auto gridRenderable = std::make_unique<Grid>();

    auto goldCubeMaterial = std::make_shared<PBRTextured>("Assets/Textures/PBR/Gold", true);
    auto wall = std::make_shared<PBRTextured>("Assets/Textures/PBR/Wall", false);
    auto goldCubeRenderable = std::make_unique<Renderable>(sphereGeometry, goldCubeMaterial);
    goldCubeRenderable->transformations->setPosition(-3.0f, 1.0f, 0.0f);
    goldCubeRenderable->castsShadwo = true;

    auto sunbro_helmet = std::make_unique<ModelSceneNode>("Assets/Model/sunbro_helmet/scene.gltf", goldCubeMaterial);
    sunbro_helmet->transformation->setRotations(glm::vec3(-90.0f, 0.0f, 00.0f));
    sunbro_helmet->transformation->setPosition(glm::vec3(0.0F, 2.0F, 0.0f));
    sunbro_helmet->transformation->setScale(glm::vec3(0.07f));
    sunbro_helmet->castsShadow(true);

    auto sword  = std::make_unique<ModelSceneNode>("Assets/Model/sword/scene.gltf");
    sword->transformation->setScale(glm::vec3(0.09f));
    sword->transformation->setPosition(glm::vec3(5.0f, 2.0f, 0.0f));
    sword->castsShadow(true);

    auto pot = std::make_unique<ModelSceneNode>("Assets/Model/pot/brass_pot_01_2k.gltf");
    pot->transformation->setPosition(-5.0f, 0.0f, 0.0f);
    pot->transformation->setScale(4.0f, 4.0f, 4.0f);
    pot->castsShadow(true);

    auto withcerMedailon = std::make_unique<ModelSceneNode>( "Assets/Model/witcher_medalion/scene.gltf");
    withcerMedailon->transformation->setRotations(glm::vec3(-90.0f, -90.0f, 0.0f));
    withcerMedailon->transformation->setPosition(glm::vec3(10.0f, 2.0f, 0.0f));
    withcerMedailon->transformation->setScale(glm::vec3(0.3));

    auto gridSceneNode = std::make_unique<SceneNode>(std::move(gridRenderable));
    gridSceneNode->transformation->setPosition(glm::vec3(0.0f, -0.2f, 0.0f));

    auto floor = std::make_unique<Renderable>(planeGeometry, wall);
    floor->transformations->setScale(10.0f, 1.0f, 10.0f);
    floor->recievesShadow = true;

    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    scene->setIblPipeLine(iblPipeLine);

    scene->add(std::move(goldCubeRenderable));
    scene->add(std::move(sunbro_helmet));
    scene->add(std::move(sword));
    scene->add(std::move(withcerMedailon));
    //scene->add(std::move(gridSceneNode));
    scene->add(std::move(floor));
    scene->add(std::move(skyboxCube));
    scene->add(std::move(pot));

    pabloRenderer->attachScene(scene);

    pabloRenderer->setDebugTexture(iblPipeLine->iblTextures[3]->type);

    pabloRenderer->render();


    return 0;
}
