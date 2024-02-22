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

//screen coordinates
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_SAMPLES, 16);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Pablo-renderer", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //this code is to make context on the window current and to initialize glad
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_FRAMEBUFFER_SRGB);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glEnable(GL_BLEND);
    glDisable(GL_CULL_FACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::unique_ptr<Shader> PBRShader = std::make_unique<Shader>("VertexShader/PBR/PBRVertex.glsl", "FragmentShader/PBR/PBRFragmentTextures.glsl", "PBR shader");
    std::unique_ptr<Shader> PBRColorShader = std::make_unique<Shader>("VertexShader/PBR/PBRVertex.glsl", "FragmentShader/PBR/PBRFragment.glsl", "PBR shader2");
    std::unique_ptr<Shader> PBRTexturedModel = std::make_unique<Shader>("VertexShader/PBR/PBRVertex.glsl", "FragmentShader/PBR/PBRFragment-Textured-Model.glsl", "PBRTexturedModel");
    std::unique_ptr<Shader> shadowMapShader = std::make_unique<Shader>("VertexShader/AdvancedLightning/ShadowMapVertex.glsl", "FragmentShader/AdvancedLightning/ShadowMapFragement.glsl", "shadow map");
    std::unique_ptr<Shader> floorShader = std::make_unique<Shader>("VertexShader/FloorVertex.glsl", "FragmentShader/FloorFragment.glsl", "floor");
    std::unique_ptr<Shader> finalShaderStage = std::make_unique<Shader>("VertexShader/AdvancedLightning/FinalVertex.glsl", "FragmentShader/AdvancedLightning/FinalFragment.glsl", "final shader");
    std::unique_ptr<Shader> hdrToCubeMapShader = std::make_unique<Shader>("VertexShader/PBR/HDRtoCubeMapVertex.glsl", "FragmentShader/PBR/HDRtoCubeMapFragment.glsl", "Cube map shader");
    std::unique_ptr<Shader> envToIrrandianceShader = std::make_unique<Shader>("VertexShader/PBR/HDRtoCubeMapVertex.glsl", "FragmentShader/PBR/EnviromentToIrradianceFragment.glsl", "Irradiance map shader");
    std::unique_ptr<Shader> skyBoxShader = std::make_unique<Shader>("VertexShader/PBR/SkyBoxVertex.glsl", "FragmentShader/PBR/SkyBoxFragment.glsl", "Sky box shader");
    std::unique_ptr<Shader> envToPrefilter = std::make_unique<Shader>("VertexShader/PBR/HDRtoCubeMapVertex.glsl", "FragmentShader/PBR/PrefilteringHDRFragment.glsl", "Prefiltering cubeData map");
    std::unique_ptr<Shader> brdfLutTextureShader = std::make_unique<Shader>("VertexShader/PBR/LutTextureVertex.glsl", "FragmentShader/PBR/BRDFLutFragment.glsl", "LUT_Textue map");
    std::unique_ptr<Shader> lutDebug = std::make_unique<Shader>("VertexShader/LutTextureDebugVertex.glsl", "FragmentShader/LutTextureDebugFragment.glsl", "LUT_Texture_qDEBUG");
    std::unique_ptr<Shader> proceduralFloorTextureShader = std::make_unique<Shader>("VertexShader/FloorGridVertex.glsl", "FragmentShader/FloorGridFragment.glsl", "Floor grid baker");

    std::unique_ptr<Geometry> cubeGeometry = std::make_unique<CubeGeometry>();
    std::unique_ptr<Geometry> planeGeometry = std::make_unique<PlaneGeometry>();

    //std::unique_ptr<IBLPipeLine> iblPipeLine = std::make_unique<IBLPipeLine>("Assets/Textures/HDR/sunrise.hdr");
    //iblPipeLine->generateIBLTextures();

    //std::unique_ptr<Material> skyBox = std::make_unique<SkyBoxMaterial>(std::move(skyBoxShader), std::move(iblPipeLine->envMap), "enviromentMap");

    //create renderable object
    //std::unique_ptr<Renderable> skyboxCube = std::make_unique<Renderable>(std::move(cubeGeometry), std::move(skyBox));

    std::unique_ptr<Renderable> gridRenderable = std::make_unique<Grid>();

    std::unique_ptr<ModelSceneNode> sunbro_helmet = std::make_unique<ModelSceneNode>(std::move(PBRTexturedModel), "Assets/Model/sunbro_helmet/scene.gltf");
    sunbro_helmet->setRotations(glm::vec3(-90.0f, 0.0f, 00.0f));
    sunbro_helmet->setPositions(glm::vec3(0.0F, 2.0F, 0.0f));
    sunbro_helmet->setScale(glm::vec3(0.07f));

    std::unique_ptr<ModelSceneNode> sword  = std::make_unique<ModelSceneNode>(std::move(PBRTexturedModel), "Assets/Model/sword/scene.gltf");
    sword->setScale(glm::vec3(0.09f));
    sword->setPositions(glm::vec3(5.0f, 2.0f, 0.0f));

    std::unique_ptr<ModelSceneNode> withcerMedailon = std::make_unique<ModelSceneNode>(std::move(PBRTexturedModel), "Assets/Model/witcher_medalion/scene.gltf");
    withcerMedailon->setRotations(glm::vec3(-90.0f, -90.0f, 0.0f));
    withcerMedailon->setPositions(glm::vec3(10.0f, 2.0f, 0.0f));
    withcerMedailon->setScale(glm::vec3(0.3));

    std::unique_ptr<SceneNode> gridSceneNode = std::make_unique<SceneNode>(std::move(gridRenderable));
    gridSceneNode->setPositions(glm::vec3(0.0f, -0.2f, 0.0f));

    std::shared_ptr<Scene> scene = std::make_shared<Scene>();
    scene->add(std::move(sunbro_helmet));
    scene->add(std::move(sword));
    scene->add(std::move(withcerMedailon));
    scene->add(std::move(gridSceneNode));
    //scene->add(std::move(skyboxCube));

    PabloRenderer pabloRenderer(scene, window);

    pabloRenderer.init();

    //------------------
    // LOAD PBR TEXTURES
    //------------------
    pabloRenderer.render();

    return 0;
}
