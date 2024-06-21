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
    inline static float pointerX = 0;
    inline static float pointerY = 0;
    inline static int screen_W ;
    inline static int screen_H ;
    inline static bool isMousePressed = false;
    inline static bool isCtrlPressed = false;
public:
    inline static bool canProcessMouse = false;

    inline static void setInstance(PabloRenderer* inst){
        instance = inst;
    }


   float getClickedObject(int x, int y) const;


    inline static PabloRenderer* getInstance(){return instance;}

    /***
     * Process resize event of the window
     * @param window window which triggers the event
     */
    static void processResize(GLFWwindow *window);

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

    /***
     * Function that process when mouse button is pressed
     * @param window window in which to process the event
     * @param button which mouse button was pressed
     * @param action what action happened (press, double click etc...)
     * @param mods what mode was button pressed with (right alt...)
     */
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);


    /***
     * Gets mouse pointer position on the window
     * @param normalize should coordinates be in the NDC (-1,1)
     * @def false
     * @return 2 component vector of mouse positions
     */
    static glm::vec2 getPointerPosition(bool normalize = false);

    static glm::vec2 getPointerPositionTransfmed(int x, int y, int displayWidth = 1980, int displayHeight = 1980, int pickingWidth = 800, int pickingHeight = 600);

    static glm::vec2 getScreenDimensions(int marginX = 0, int marginY = 0){return {screen_W- marginX, screen_H-marginY};};

    static int getScreenWidth(int margin = 0) {return GLFWHelper::screen_W - margin;};

    static int getScreenHeight(int margin = 0) {return GLFWHelper::screen_H- margin;};

    static glm::vec2 getDefaultFrameBufferDimentions();
};


#endif //PABLO_RENDERER_GLFWHELPER_H
