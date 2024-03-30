#include <glad/glad.h>
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
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;


int main() {

    auto pabloRenderer = PabloRenderer::getInstance();
    pabloRenderer->init(SCR_WIDTH, SCR_HEIGHT);

    auto PBRShader = std::make_shared<Shader>("VertexShader/PBR/PBRVertex.glsl", "FragmentShader/PBR/PBRFragmentTextures.glsl", "PBR shader");
    auto PBRColorShader = std::make_shared<Shader>("VertexShader/PBR/PBRVertex.glsl", "FragmentShader/PBR/PBRFragment.glsl", "PBR shader2");
    auto PBRTexturedModel = std::make_shared<Shader>("VertexShader/PBR/PBRVertex.glsl", "FragmentShader/PBR/PBRFragment-Textured-Model.glsl", "PBRTexturedModel");
    auto shadowMapShader = std::make_shared<Shader>("VertexShader/AdvancedLightning/ShadowMapVertex.glsl", "FragmentShader/AdvancedLightning/ShadowMapFragement.glsl", "shadow map");
    auto floorShader = std::make_shared<Shader>("VertexShader/FloorVertex.glsl", "FragmentShader/FloorFragment.glsl", "floor");
    auto finalShaderStage = std::make_shared<Shader>("VertexShader/AdvancedLightning/FinalVertex.glsl", "FragmentShader/AdvancedLightning/FinalFragment.glsl", "final shader");
    auto hdrToCubeMapShader = std::make_shared<Shader>("VertexShader/PBR/HDRtoCubeMapVertex.glsl", "FragmentShader/PBR/HDRtoCubeMapFragment.glsl", "Cube map shader");
    auto skyBoxShader = std::make_shared<Shader>("VertexShader/PBR/SkyBoxVertex.glsl", "FragmentShader/PBR/SkyBoxFragment.glsl", "Sky box shader");
    auto brdfLutTextureShader = std::make_shared<Shader>("VertexShader/PBR/LutTextureVertex.glsl", "FragmentShader/PBR/BRDFLutFragment.glsl", "LUT_Textue map");
    auto lutDebug = std::make_shared<Shader>("VertexShader/LutTextureDebugVertex.glsl", "FragmentShader/LutTextureDebugFragment.glsl", "LUT_Texture_qDEBUG");
    auto proceduralFloorTextureShader = std::make_shared<Shader>("VertexShader/FloorGridVertex.glsl", "FragmentShader/FloorGridFragment.glsl", "Floor grid baker");

    auto PBRTexutreIBLOBJ = std::make_shared<Shader>("VertexShader/PBR/PBRVertex.glsl","FragmentShader/PBR/PBRFragment-IBL-textured-object.glsl", "PBR For simple geometry");
    PBRTexutreIBLOBJ->supportsIBL = true;

    auto PBRTexturedModelIBL = std::make_shared<Shader>("VertexShader/PBR/PBRVertex.glsl", "FragmentShader/PBR/PBRFragment-IBL-textured.glsl", "PBR_IBL");
    PBRTexturedModelIBL->supportsIBL = true;

    auto iblPipeLine = std::make_shared<IBLPipeLine>("Assets/Textures/HDR/sunset.hdr");
    iblPipeLine->generateIBLTextures();

    auto cubeGeometry = std::make_shared<CubeGeometry>();
    auto planeGeometry = std::make_shared<PlaneGeometry>();
    auto sphereGeometry = std::make_shared<SphereGeometry>();

    auto skyBox = std::make_unique<SkyBoxMaterial>(std::move(skyBoxShader), *iblPipeLine->envMap, "enviromentMap");

    //create renderable object
    auto skyboxCube = std::make_unique<Renderable>(cubeGeometry, std::move(skyBox));

    auto gridRenderable = std::make_unique<Grid>();

    auto goldCubeMaterial = std::make_shared<PBRTextured>(PBRTexutreIBLOBJ, "Assets/Textures/PBR/Gold");
    auto goldCubeRenderable = std::make_unique<Renderable>(sphereGeometry, goldCubeMaterial);
    goldCubeRenderable->transformations->setPosition(-3.0f, 1.0f, 0.0f);
    goldCubeRenderable->castsShadwo = true;

    auto sunbro_helmet = std::make_unique<ModelSceneNode>(PBRTexturedModelIBL, "Assets/Model/sunbro_helmet/scene.gltf");
    sunbro_helmet->transformation->setRotations(glm::vec3(-90.0f, 0.0f, 00.0f));
    sunbro_helmet->transformation->setPosition(glm::vec3(0.0F, 2.0F, 0.0f));
    sunbro_helmet->transformation->setScale(glm::vec3(0.07f));

    auto sword  = std::make_unique<ModelSceneNode>(PBRTexturedModelIBL, "Assets/Model/sword/scene.gltf");
    sword->transformation->setScale(glm::vec3(0.09f));
    sword->transformation->setPosition(glm::vec3(5.0f, 2.0f, 0.0f));

    auto withcerMedailon = std::make_unique<ModelSceneNode>(PBRTexturedModelIBL, "Assets/Model/witcher_medalion/scene.gltf");
    withcerMedailon->transformation->setRotations(glm::vec3(-90.0f, -90.0f, 0.0f));
    withcerMedailon->transformation->setPosition(glm::vec3(10.0f, 2.0f, 0.0f));
    withcerMedailon->transformation->setScale(glm::vec3(0.3));

    auto gridSceneNode = std::make_unique<SceneNode>(std::move(gridRenderable));
    gridSceneNode->transformation->setPosition(glm::vec3(0.0f, -0.2f, 0.0f));

    auto floor = std::make_unique<Renderable>(planeGeometry, goldCubeMaterial);

    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    scene->setIblPipeLine(iblPipeLine);

    scene->add(std::move(goldCubeRenderable));
    scene->add(std::move(sunbro_helmet));
    scene->add(std::move(sword));
    scene->add(std::move(withcerMedailon));
    scene->add(std::move(gridSceneNode));
    scene->add(std::move(skyboxCube));

    pabloRenderer->attachScene(scene);

    pabloRenderer->setDebugTexture(iblPipeLine->iblTextures[3]->type);

    pabloRenderer->render();


    return 0;
}
