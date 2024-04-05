//
// Created by wpsimon09 on 05/04/24.
//

#ifndef PABLO_RENDERER_RENDERERMANAGER_H
#define PABLO_RENDERER_RENDERERMANAGER_H

#include "iostream"
#include "memory"
#include "Renderer/Renderers/OGLRenderer/OGLRenderer.h"
#include "Renderer/Renderers/DepthRenderer/DepthRenderer.h"

enum RENDERER_TYPE{
    COLOR_DEPTH_STENCIL = 1,
    DEPTH_ONLY = 2
};

class RendererManager {
public:
    RendererManager();

    inline static std::vector<std::shared_ptr<OGLRenderer>> renderers;

    static std::shared_ptr<OGLRenderer> requestRenderer(RENDERER_TYPE type = COLOR_DEPTH_STENCIL);
};


#endif //PABLO_RENDERER_RENDERERMANAGER_H
