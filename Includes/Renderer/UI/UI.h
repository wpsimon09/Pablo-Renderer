//
// Created by wpsimon09 on 15/04/24.
//

#ifndef PABLO_RENDERER_UI_H
#define PABLO_RENDERER_UI_H
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "Shader.h"
#include "memory"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"

class UI {
public:
    /**
     * @brief Initializes the UI
     * @param window window which is used by the UI
     */
    static void init(GLFWwindow* window);

    /**
     * @brief Renders the acctual UI
     */
    static void render();

    /**
     * @brief Terminates the UI
     */
    static void terminate();

    /**
     * @brief Sets value to be passed to the shader
     * @tparam T type of the value in Shader
     * @param shader shader to be utilized
     * @param value value to be passed to the shader
     */
    template<class T>
    static void setShaderValue(std::shared_ptr<Shader> shader,T value);

    /**
     * @brief Sets the image to be displayed on the view port window @see @class ViewPort
     * @param image image to be displayed on the view port window
     * @note mainly used in RenderPasses and the last render pass should be dispalyed here
     */
    static void setRenderedSceneImage(std::shared_ptr<Texture2D> image){ renderedScene = image;}

    /**
     * @brief Sets the image of the debug texture
     * @param image Image to be displayed in debug texture
     * @deprecated this is no longer usefull as there is no debug texture available at this poing
     */
    static void setDebugImage(std::shared_ptr<Texture2D> image){debugTexture = image;}

    /**
     * @brief Retrieves ImGui instacne @link https://github.com/ocornut/imgui
     * @return IMGUI instace IO
     */
    static ImGuiIO* getIo(){return imGuiIo;}

    /**
     * @brief Helper method to convert from ImVec2 to teh glm::vec2 vectors
     * @param vector vector to be converted
     * @return same vector in ImVec2 type
     * @todo add backwards conversion
     */
    inline static ImVec2 glm2ImGUI(glm::vec2 vector){
        return ImVec2(vector.x, vector.y);
    }
private:
    /**
     * @brief IO of the IM::GUI instance
     */
    inline static ImGuiIO* imGuiIo;


    inline static bool show_debug_texture = false;

    inline static std::shared_ptr<Texture2D> debugTexture;
    inline static std::shared_ptr<Texture2D> renderedScene;

};


#endif //PABLO_RENDERER_UI_H
