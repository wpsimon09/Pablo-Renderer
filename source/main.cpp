#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"
#include "HelperFunctions.h"
#include "DrawingFunctions.h"
#include "VaoCreation.h"
#include "PBRPipeline/PBRPipeline.h"
#include "Model.h"
#include "Debug/DisplayingFrameBuffer/FrameBufferDebug.h"
#include "Renderer/Geometry/Geometry.h"
#include "Renderer/Geometry/Shapes/Cube/CubeGeometry.h"
#include "Renderer/Geometry/Shapes/Plane/PlaneGeometry.h"
#include "Renderer/Geometry/Shapes/ScreenSpaceQuad/ScreenSpaceQuadGeometry.h"
#include "Renderer/Utils/Texture/Texture2D.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Material/PBRColor/PBRColor.h"
#include "Renderer/Material/PBRTexture/PBRTextured.h"
#include "Renderer/Renderable/Renderable.h"
#include "Renderer/SceneGraph/Scene.h"
#include "Renderer/Renderers/OGLRenderer/OGLRenderer.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

float opacityOfTexture(GLFWwindow* window, Shader shader);

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

//screen coordinates
int SCR_WIDTH = 800;
int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
bool firstMouse = true;

float hasNormalMap = 1.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

glm::vec3 lightColor = COLOR_SUN;

//light possition
glm::vec3 lightPosition(0.0f, 2.0f, -1.0f);


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_SAMPLES, 8);
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
    //enables gama correction that is build in opengl
    glEnable(GL_FRAMEBUFFER_SRGB);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glEnable(GL_BLEND);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    unsigned int rows = 5;
    unsigned int colums = 5;
    unsigned int totalAmount = rows * colums;

    Shader PBRShader("VertexShader/PBR/PBRVertex.glsl", "FragmentShader/PBR/PBRFragment-IBL-textured.glsl", "PBR shader");

    Shader PBRColorShader("VertexShader/PBR/PBRVertex.glsl", "FragmentShader/PBR/PBRFragment.glsl", "PBR shader");

    Shader lightSourceShader("VertexShader/AdvancedLightning/LightSourceVertex.glsl", "FragmentShader/AdvancedLightning/LightSourceFragment.glsl", "light sourece");

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

    Shader frameBufferDebugShader("VertexShader/FrameBufferDebugVertex.glsl","FragmentShader/FrameBufferDebugFragment.glsl", "Texturedebug shader");
    //witcher medailon
    Model witcherMedailon("Assets/Model/witcher_medalion/scene.gltf");

    //witcher medailon
    Model mortier("Assets/Model/medieval_mortier/scene.gltf");

    new CubeGeometry("cube");

    Geometry* planeGeometry;
    planeGeometry = new PlaneGeometry("plane");

    Geometry* screenSpaceQuadGeometry;
    screenSpaceQuadGeometry = new ScreenSpaceQuadGeometry("ss-quad");
    stbi_set_flip_vertically_on_load(true);

    // plane VAO
    unsigned int screeneSpaceQuadVAO = createVAO(screeneSpaceQuadVertecies, sizeof(screeneSpaceQuadVertecies) / sizeof(float), false, true);

    //VBO, EBO and VAO for the square that represents light position
    unsigned int lightVAO = createVAO(lightVertices, sizeof(lightVertices) / sizeof(float), false);

    //cubeData VAO
    unsigned int cubeVAO = createVAO(cubeVertices, sizeof(cubeVertices) / sizeof(float));

    //debug quad VAO
    unsigned int debugQuadVao = createVAO(debugQuadVertices, sizeof(debugQuadVertices)/sizeof(float), false, true);

    //sphereVAO
    unsigned int indexNum;
    unsigned int instanceCount;
    unsigned int sphereVAO = createSphereVAO(indexNum);

    //-------------------
    // SHADOW MAP TEXTURE
    //-------------------

    //resolution of the depth map
    const unsigned int SHADOW_HEIGHT = 1980, SHADOW_WIDTH = 1980;
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);

    //NOTE how we set a texture type to be GL_DEPTH_COMPONENT instead GL_RGB or GL_RGBA
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    //set the textures prameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    //-------------------
    // SHADOW MAPPING FBO
    //-------------------
    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);

    //attatch texture to the frame buffer depth value
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    //we are not going to need the color buffer
    //we tell this to openGl like so
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindBuffer(GL_FRAMEBUFFER, 0);

    //-----------------
    // TEXTURES LOADING
    //-----------------
    Texture2D cubeTexture("Assets/Textures/container.jpg");
    unsigned int floorTexture = loadTexture("Assets/Textures/AdvancedLightning/grid_w.jpg", true);
    unsigned int pointLightTexture = loadTexture("Assets/Textures/AdvancedLightning/light.png", false);
    unsigned int dirLightTexture = loadTexture("Assets/Textures/AdvancedLightning/sun.png", false);
    unsigned int brickWall = loadTexture("Assets/Textures/AdvancedLightning/brickwall.jpg", false);
    unsigned int normalMap = loadTexture("Assets/Textures/AdvancedLightning/brickwall_normal.jpg", false);
    unsigned int floorNormalMap = loadTexture("Assets/Textures/AdvancedLightning/floor_normal.jpg", false);
    unsigned int hdrTexture = loadIrradianceMap("Assets/Textures/HDR/forest.hdr");

    glm::vec3 lightPositions[] = {
            glm::vec3(-10.0f,  10.0f, 10.0f),
            glm::vec3(10.0f,  10.0f, 10.0f),
            glm::vec3(-10.0f, -10.0f, 10.0f),
            glm::vec3(10.0f, -10.0f, 10.0f),
    };
    glm::vec3 lightColors[] = {
            glm::vec3(300.0f, 300.0f, 300.0f),
            glm::vec3(300.0f, 300.0f, 300.0f),
            glm::vec3(300.0f, 300.0f, 300.0f),
            glm::vec3(300.0f, 300.0f, 300.0f)
    };
    int nrRows = 7;
    int nrColumns = 7;
    float spacing = 2.5;

    //----------------
    //Scene
    //----------------

    //cerate material properties
    Material *cubeBasicMaterial = new PBRColor(&PBRColorShader);
    Geometry *cubeGeometry = new ScreenSpaceQuadGeometry();

    //create renderable object
    Renderable basicCube(cubeGeometry,cubeBasicMaterial);

    //optional create scene node
    SceneNode cube(&basicCube);
    //cube.setScale(glm::vec3(1.0f, 0.0f, 1.0f));
    cube.setPositions(glm::vec3(2.0f, 0.0f, 0.0f));

    //create scene object
    SceneNode cube2(&basicCube);
    cube2.setPositions(glm::vec3(0.0f, 0.0f, 0.0f));
    cube2.setScale(glm::vec3(10.0f, 1.0f, 1.2f));
    cube2.setRotations(glm::vec3(0.0F, 80.0f, 0.0f));

    Scene scene;
    scene.add(&cube);
    scene.add(&cube2);

    OGLRenderer renderer(&scene);

    //-------------
    // PBR PIPELINE
    //-------------
    PBRPipeline pbrPipeline(hdrTexture);
    pbrPipeline.generateHdrCubeMap(hdrToCubeMapShader, cubeVAO);
    pbrPipeline.generateIrradianceMap(envToIrrandianceShader, pbrPipeline.getHdrCubeMap(),cubeVAO);
    pbrPipeline.generatePrefilterMap(envToPrefilter, pbrPipeline.getHdrCubeMap(), cubeVAO);
    pbrPipeline.generateBrdfLutTexture(brdfLutTextureShader, screenSpaceQuadGeometry->getVertexArrays());

    //-------------------------
    // FLOOR PROCEDURAL TEXTURE
    //-------------------------
    FrameBuffer proceduralTextureFrameBuffer;
    Texture *girdProceduralTexture = new Texture(GL_TEXTURE_2D, "gridTexture", glm::vec2(512, 512), GL_RGBA, GL_RGBA);
    proceduralTextureFrameBuffer.mountTexture(girdProceduralTexture);
    girdProceduralTexture->changeWrappingMethod(GL_REPEAT, GL_REPEAT);
    proceduralTextureFrameBuffer.updateRenderBufferStorage(girdProceduralTexture->getDimentions());
    proceduralFloorTextureShader.use();
    proceduralFloorTextureShader.setFloat("numOfDivisions", 1.2);
    proceduralTextureFrameBuffer.drawToTexture(proceduralFloorTextureShader, screeneSpaceQuadVAO);

    //--------------------------
    // DEBUG VIEW FOR THE CAMERA
    //--------------------------
    FrameBufferDebug frameBufferDebugWindow(GL_TEXTURE_2D, "debug", glm::vec2(124, 124), GL_RGBA, GL_RGBA32F);


    //------------------
    // LOAD PBR TEXTURES
    //------------------
    PBRShader.use();
    PBRShader.setInt("irradianceMap", 5);
    PBRShader.setInt("prefilterMap", 6);
    PBRShader.setInt("BRDFtexture", 7);

    lutDebug.use();
    lutDebug.setInt("LUTTexture", 0);

    floorShader.use();
    floorShader.setInt("texture_diffuse0", 0);
    floorShader.setInt("shadowMap", 1);

    lightSourceShader.use();
    lightSourceShader.setInt("lightTexture", 0);

    skyBoxShader.use();
    skyBoxShader.setInt("enviromentMap", 0);
    //=====================================================================================//
    //==================================== RENDER LOOOP ===================================//
    //=====================================================================================//
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        //--------------------------------------//
        //------------- DEPTH MAP -------------//
        //------------------------------------//

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        // configure projection matrix
        float nearPlane, farPlane;
        nearPlane = 1.0f;
        farPlane = 75.0f;
        glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, nearPlane, farPlane);

        //configure view matrix
        glm::mat4 lightView = glm::lookAt(lightPosition, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));

        //combine them together to get the matrix that transfoms coordinates from view space to light space
        // in the notes as T
        glm::mat4 lightSpaceMatrix = lightProjection * lightView;

        glm::mat4 lightModel = glm::mat4(1.0f);
        lightModel = glm::scale(lightModel, glm::vec3(6.0f));
        //draw the scene to the depth map
        glCullFace(GL_FRONT);
        shadowMapShader.use();
        lightModel = glm::rotate(lightModel, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        shadowMapShader.setMat4("model", lightModel);
        witcherMedailon.Draw(PBRShader);

        glCullFace(GL_BACK);

        //--------------------------------------//
        //---------- NORMAL SCENE -------------//
        //------------------------------------//
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.01f, 0.01f, 0.01f, 1.0f);

        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 model = glm::mat4(1.0f);

        //-----------------
        // DRAW THE SPHERES
        //-----------------
        glDisable(GL_CULL_FACE);
        PBRShader.use();
        PBRShader.setVec3("camPos", camera.Position);

        //------------------------------
        //DRAW CUBE FROM THE SCENE GRAPH
        //------------------------------
        PBRShader.use();
        PBRShader.setMat4("view", view);
        PBRShader.setMat4("projection", projection);

        renderer.render(window);

        //-------------
        // DRAW MODEL
        //-------------
        model = glm::translate(model, glm::vec3(0.0f, 3.0f, 0.0f));
        model = glm::rotate(model,glm::radians(-90.0f),glm::vec3(1.0,0.0,0.0));
        PBRShader.use();
        PBRShader.setMat4("model", model);
        PBRShader.setMat3("normalMatrix", glm::transpose(glm::inverse(model)));
        PBRShader.setMat3("normalMatrix", glm::transpose(glm::inverse(model)));
        pbrPipeline.bindTextures(5);

        witcherMedailon.Draw(PBRShader);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
        model = glm::rotate(model,glm::radians(-90.0f),glm::vec3(1.0,0.0,0.0));
        model = glm::scale(model, glm::vec3(4.0f));
        PBRShader.setMat4("model", model);
        mortier.Draw(PBRShader);



        //set light properties
        for (unsigned int i = 0; i < 5; ++i)
        {
            PBRShader.use();
            if (i <= 4)
            {
                PBRShader.setVec3("lightPositions[" + std::to_string(i) + "]", lightPositions[i]);
                PBRShader.setVec3("lightColors[" + std::to_string(i) + "]", lightColors[i]);
            }
            else
            {
                PBRShader.setVec3("lightPositions[" + std::to_string(i) + "]", lightPosition);
                PBRShader.setVec3("lightColors[" + std::to_string(i) + "]", lightColor);
            }

        }

        //-----------------------
        // DRAW THE LIGHT SOURCES
        //-----------------------
        lightSourceShader.use();
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPosition);

        for (unsigned int i = 0; i < 4; ++i)
        {
            glm::vec3 newPos = lightPositions[i];
            model = glm::mat4(1.0f);
            model = glm::translate(model, newPos);
            model = glm::scale(model, glm::vec3(0.5f));
            lightSourceShader.use();
            lightSourceShader.setMat4("model", model);
            lightSourceShader.setVec3("lightColor", lightColors[i]);
            useTexture(0, pointLightTexture);
            DrawPlane(lightSourceShader, model, view, projection, lightVAO, GL_TRIANGLES, 6);
        }

        PBRShader.use();
        PBRShader.setVec3("lightPositions[4]", lightPosition);
        PBRShader.setVec3("lightColors[4]", lightColors[1]);

        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPosition);
        model = glm::scale(model, glm::vec3(0.5f));
        lightSourceShader.use();
        lightSourceShader.setMat4("model", model);
        lightSourceShader.setVec3("lightColor", lightColor);
        useTexture(0, dirLightTexture);
        DrawPlane(lightSourceShader, model, view, projection, lightVAO);

        //------------
        // DRAW SKYBOX
        //------------
        skyBoxShader.use();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP,pbrPipeline.getHdrCubeMap()); //pbrPipeline.getHdrCubeMap());
        //DrawCube(skyBoxShader, model, view, projection, cubeGeometry->getVertexArrays());


        //----------------------
        // DRAW PLANE AS A FLOOR
        //----------------------
        floorShader.use();
        useTexture(0, girdProceduralTexture->ID);
        useTexture(1, depthMap);
        model = glm::mat4(1.0f);
        floorShader.setMat4("lightMatrix", lightSpaceMatrix);
        floorShader.setVec3("lightPos", lightPosition);
        floorShader.setVec3("lightColor", lightColor);
        floorShader.setVec3("viewPos", camera.Position);
        DrawPlane(floorShader, model, view, projection, planeGeometry->getVertexArrays(), GL_TRIANGLES, 6);

        //----------------------
        // DRAW BRDF LUT TEXTURE
        //----------------------
        /*
        lutDebug.use();
        useTexture(0, pbrPipeline.getBrdfLutTexture());
        DrawPlane(lutDebug, glm::mat4(1.0), glm::mat4(1.0), glm::mat4(1.0), screenSpaceQuadGeometry->getVertexArrays(), GL_TRIANGLE_STRIP, 4);
         */


        //-----------------
        //DRAW DEBUG WINDOW
        //-----------------
        frameBufferDebugWindow.draw(frameBufferDebugShader, debugQuadVao,cubeTexture.ID);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}

//function that will handle resizing of the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    const float lightSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        lightPosition.z += lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        lightPosition.z -= lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        lightPosition.x += lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        lightPosition.x -= lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        lightPosition.y -= lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        lightPosition.y += lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
        hasNormalMap = 1.0f;
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
        hasNormalMap = 0.0f;

}

float opacityOfTexture(GLFWwindow* window, Shader shader) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        return 0.001f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        return -0.001f;
    }
    return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

    if (firstMouse) // initially set to true
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xOffset = xpos - lastX;
    float yOffset = ypos - lastY; //calculate how much does mouse move

    lastX = xpos;
    lastY = ypos; //update last mouse position

    camera.ProcessMouseMovement(xOffset, yOffset);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
