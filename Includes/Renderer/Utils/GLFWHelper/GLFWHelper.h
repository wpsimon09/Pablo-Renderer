//
// Created by wpsimon09 on 19/03/24.
//

#ifndef PABLO_RENDERER_GLFWHELPER_H
#define PABLO_RENDERER_GLFWHELPER_H

#include "Renderer/PabloRenderer.h"

class PabloRenderer;
class GLFWHelper {
private:
    inline static PabloRenderer *instance;
public:
    GLFWHelper(){
        GLFWHelper::instance = PabloRenderer::getInstance();
    };
    
    /***
    * Process the input for the application
    * @param window window in which to process the input
    */
    static void processInput(GLFWwindow *window, float deltaTime);

    /***
     * Processes event when mouse wheel has scrolled
     * @param window window in which to event occurred
     * @param xoffset offset on x axis
     * @param yoffset offset on y axis
     */
    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

    /***
     * Function that process mouse movement call back
     * @param window window in which to process the callback
     * @param xpos position on x axis
     * @param ypos position on y axis
     */
    static void mouse_callback(GLFWwindow *window, double xpos, double ypos);

    /***
     * Initializes OpenGL context
     * @param width width of the window
     * @param height height of the height
     * @return true if the context was initialized otherwise false
     */
    static bool glInit(unsigned int width, unsigned int height);


};


#endif //PABLO_RENDERER_GLFWHELPER_H
