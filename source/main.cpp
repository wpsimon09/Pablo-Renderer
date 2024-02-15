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

    Shader PBRShader("VertexShader/PBR/PBRVertex.glsl", "FragmentShader/PBR/PBRFragmentTextures.glsl", "PBR shader");

    Shader PBRColorShader("VertexShader/PBR/PBRVertex.glsl", "FragmentShader/PBR/PBRFragment.glsl", "PBR shader2");

    Shader PBRTexturedModel("VertexShader/PBR/PBRVertex.glsl","FragmentShader/PBR/PBRFragment-Textured-Model.glsl", "PBRTexturedModel");

    Shader shadowMapShader("VertexShader/AdvancedLightning/ShadowMapVertex.glsl", "FragmentShader/AdvancedLightning/ShadowMapFragement.glsl", "shadow map");

    Shader floorShader("VertexShader/FloorVertex.glsl", "FragmentShader/FloorFragment.glsl", "floor");

    Shader finalShaderStage("VertexShader/AdvancedLightning/FinalVertex.glsl", "FragmentShader/AdvancedLightning/FinalFragment.glsl", "final shader");

    Shader hdrToCubeMapShader("VertexShader/PBR/HDRtoCubeMapVertex.glsl", "FragmentShader/PBR/HDRtoCubeMapFragment.glsl", "Cube map shader");

    Shader envToIrrandianceShader("VertexShader/PBR/HDRtoCubeMapVertex.glsl", "FragmentShader/PBR/EnviromentToIrradianceFragment.glsl", "Irradiance map shader");

    Shader skyBoxShader("VertexShader/PBR/SkyBoxVertex.glsl", "FragmentShader/PBR/SkyBoxFragment.glsl", "Sky box shader");

    Shader envToPrefilter("VertexShader/PBR/HDRtoCubeMapVertex.glsl", "FragmentShader/PBR/PrefilteringHDRFragment.glsl", "Prefiltering cubeData map");

    Shader brdfLutTextureShader("VertexShader/PBR/LutTextureVertex.glsl", "FragmentShader/PBR/BRDFLutFragment.glsl", "LUT_Textue map");

    Shader lutDebug("VertexShader/LutTextureDebugVertex.glsl", "FragmentShader/LutTextureDebugFragment.glsl", "LUT_Texture_qDEBUG");

    Shader proceduralFloorTextureShader("VertexShader/FloorGridVertex.glsl", "FragmentShader/FloorGridFragment.glsl", "Floor grid baker");

    //cerate material properties
    Material *cubeGoldMaterial = new PBRTextured(&PBRShader, "Assets/Textures/PBR/Gold");
    Material *cubeWallMaterial = new PBRTextured(&PBRShader, "Assets/Textures/PBR/Wall");
    Material *cubeRustedIron = new PBRTextured(&PBRShader, "Assets/Textures/PBR/RustedIron");

    Geometry *cubeGeometry = new CubeGeometry();
    Geometry* planeGeometry = new PlaneGeometry();



    //create renderable object
    Renderable cubeGold(cubeGeometry, cubeGoldMaterial);
    Renderable cubeWall(cubeGeometry, cubeWallMaterial);
    Renderable cubeIron(cubeGeometry, cubeRustedIron);

    Renderable *gridRenderable = new Grid();

    ModelSceneNode sunbro_helmet(&PBRTexturedModel, "Assets/Model/sunbro_helmet/scene.gltf");
    sunbro_helmet.setRotations(glm::vec3(-90.0f, 0.0f, 00.0f));
    sunbro_helmet.setPositions(glm::vec3(0.0F, 2.0F, 0.0f));
    sunbro_helmet.setScale(glm::vec3(0.07f));

    ModelSceneNode sword(&PBRTexturedModel, "Assets/Model/sword/scene.gltf");
    sword.setScale(glm::vec3(0.09f));
    sword.setPositions(glm::vec3(5.0f, 2.0f, 0.0f));

    ModelSceneNode withcerMedailon(&PBRTexturedModel, "Assets/Model/witcher_medalion/scene.gltf");
    withcerMedailon.setRotations(glm::vec3(-90.0f, -90.0f, 0.0f));
    withcerMedailon.setPositions(glm::vec3(10.0f, 2.0f, 0.0f));
    withcerMedailon.setScale(glm::vec3(0.3));

    SceneNode gridSceneNode(gridRenderable);
    gridSceneNode.setPositions(glm::vec3(0.0f, -0.2f, 0.0f));

    Scene scene;
    scene.add(&sunbro_helmet);
    scene.add(&sword);
    scene.add(&withcerMedailon);
    scene.add(&gridSceneNode);
    PabloRenderer pabloRenderer(&scene, window);

    pabloRenderer.init();

    //------------------
    // LOAD PBR TEXTURES
    //------------------
    pabloRenderer.render();

    return 0;
}
