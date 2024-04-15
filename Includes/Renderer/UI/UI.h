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

    template<class T>
    static void setShaderValue(std::shared_ptr<Shader> shader,T value);
private:
    inline static ImGuiIO* imGuiIo;
};


#endif //PABLO_RENDERER_UI_H
