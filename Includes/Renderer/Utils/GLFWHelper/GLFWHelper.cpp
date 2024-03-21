//
// Created by wpsimon09 on 19/03/24.
//

#include "GLFWHelper.h"

void GLFWHelper::processInput(GLFWwindow *window, float deltaTime) {
    instance->getScene()->light->processInput(window);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    const float lightSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        instance->getScene()->camera->ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        instance->getScene()->camera->ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        instance->getScene()->camera->ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        instance->getScene()->camera->ProcessKeyboard(RIGHT, deltaTime);
}

void GLFWHelper::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    instance->getScene()->camera->ProcessMouseScroll(static_cast<float>(yoffset));
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

    instance->getScene()->camera->ProcessMouseMovement(xOffset, yOffset);

}

bool GLFWHelper::glInit(unsigned int width, unsigned int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_SAMPLES, 8);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    instance->setWindow(glfwCreateWindow(width, height, "Pablo-renderer", NULL, NULL));
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
    glfwSetInputMode(instance->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);


    return true;
}
