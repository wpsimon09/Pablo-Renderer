//
// Created by wpsimon09 on 19/03/24.
//

#include "GLFWHelper.h"

void GLFWHelper::processInput(GLFWwindow *window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        isCtrlPressed = true;
    else
        isCtrlPressed = false;

    const float lightSpeed = 2.5f * deltaTime; // adjust accordingly
}

void GLFWHelper::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    if(UI::getIo()->WantCaptureMouse && canProcessMouse) {
        instance->getScene()->camera->zoom((float) yoffset);
    }
}

void GLFWHelper::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if(UI::getIo()->WantCaptureMouse && canProcessMouse){
        if (instance->firstMouse) {
            instance->lastX = xpos;
            instance->lastY = ypos;
            instance->firstMouse = false;
        }

        float xOffset = xpos - instance->lastX;
        float yOffset = instance->lastY - ypos; // Invert the sign here

        instance->lastX = xpos;
        instance->lastY = ypos;

        xOffset *= 0.01;
        yOffset *= 0.01;

        if (xOffset != 0.0 && isMousePressed && !isCtrlPressed) {
            instance->getScene()->camera->rotateAzimutn(xOffset);
        }

        if (yOffset != 0.0 && isMousePressed && !isCtrlPressed) {
            instance->getScene()->camera->rotatePolar(-yOffset);
        }


        GLFWHelper::pointerX = xpos;
        GLFWHelper::pointerY = ypos;
    }
}

bool GLFWHelper::glInit(unsigned int width, unsigned int height) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_SAMPLES, 4);
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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glfwSetCursorPosCallback(instance->getWindow(), mouse_callback);
    glfwSetScrollCallback(instance->getWindow(), scroll_callback);
    glfwSetInputMode(instance->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
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
    GLFWcursor* hand = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
    GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_CURSOR_NORMAL);
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        if (action == GLFW_PRESS) {
            isMousePressed = true;
            glfwSetCursor(instance->getWindow(), hand);
        } else if (action == GLFW_RELEASE) {
            isMousePressed = false;
            glfwSetCursor(instance->getWindow(), cursor);
        }
    }
}





