//
// Created by wpsimon09 on 19/03/24.
//

#include "GLFWHelper.h"

void GLFWHelper::processInput(GLFWwindow *window, float deltaTime) {
    instance->getScene()->light->processInput(window);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    const float lightSpeed = 2.5f * deltaTime; // adjust accordingly
}

void GLFWHelper::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    instance->getScene()->camera->zoom((float) yoffset);
}

void GLFWHelper::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (instance->firstMouse) // initially set to true
    {
        instance->lastX = xpos;
        instance->lastY = ypos;
        instance->firstMouse = false;
    }

    float xOffset = xpos - instance->lastX;
    float yOffset = ypos - instance->lastY; //calculate how much does mouse move

    instance->lastX = xpos;
    instance->lastY = ypos; //update last mouse position

    if(xOffset > 0 && isMousePressed){
        instance->getScene()->camera->rotateAzimutn(xOffset);
    }

    if(yOffset > 0 && isMousePressed){
        instance->getScene()->camera->rotatePolar(xOffset);
    }


    GLFWHelper::pointerX = xpos;
    GLFWHelper::pointerY = ypos;

}

bool GLFWHelper::glInit(unsigned int width, unsigned int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_SAMPLES, 8);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    screen_W = mode->width;
    screen_H = mode->height;


    instance->setWindow(glfwCreateWindow(width == 0?screen_W:width, height==0? screen_H:0, "Pablo-renderer", NULL, NULL));
    if (instance->getWindow() == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return false;
    }

    //this code is to make context on the window current and to initialize glad
    glfwMakeContextCurrent(instance->getWindow());
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
        return false;
    }

    glfwSetCursorPosCallback(instance->getWindow(), mouse_callback);
    glfwSetScrollCallback(instance->getWindow(), scroll_callback);
    glfwSetInputMode(instance->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowRefreshCallback(instance->getWindow(), processResize);
    glfwSetMouseButtonCallback(instance->getWindow(), mouse_button_callback);

    return true;
}

void GLFWHelper::processResize(GLFWwindow *window) {
    glfwGetWindowSize(instance->getWindow(), &GLFWHelper::screen_W, &GLFWHelper::screen_H);
    instance->getScene()->camera->processResize(GLFWHelper::screen_W, GLFWHelper::screen_H);
    std::cout<<GLFWHelper::screen_W<<std::endl;std::cout<<GLFWHelper::screen_H<<std::endl;

}

glm::vec2 GLFWHelper::getPointerPosition(bool normalize) {
    if(normalize){
        float mouseX_norm = (2.0 * pointerX)/GLFWHelper::screen_W - 1;
        float mouseY_norm = 1.0 - (2* pointerY)/GLFWHelper::screen_H;
        return {mouseX_norm, mouseY_norm};
    }
    return {pointerX, pointerY};
}

glm::vec2 GLFWHelper::getDefaultFrameBufferDimentions() {
    int widht, height;

    glfwGetFramebufferSize(instance->getWindow(), &widht, &height);

    return {widht, height};
}

void GLFWHelper::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        isMousePressed = true;
        std::cout<<"pressed"<<std::endl;
    }
    else{
        isMousePressed = false;
    }
}





