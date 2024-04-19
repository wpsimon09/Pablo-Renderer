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
    static void init(GLFWwindow* window);

    static void render();

    static void terminate();

    template<class T>
    static void setShaderValue(std::shared_ptr<Shader> shader,T value);

    static void setRenderedSceneImage(std::shared_ptr<Texture2D> image){ renderedScene = image;}
    static void setDebugImage(std::shared_ptr<Texture2D> image){debugTexture = image;}

    static ImGuiIO* getIo(){return imGuiIo;}
private:
    inline static ImGuiIO* imGuiIo;

    inline static ImVec2 glm2ImGUI(glm::vec2 vector){
        return ImVec2(vector.x, vector.y);
    }

    inline static bool show_debug_texture = false;

    inline static std::shared_ptr<Texture2D> debugTexture;
    inline static std::shared_ptr<Texture2D> renderedScene;

};


#endif //PABLO_RENDERER_UI_H
