//
// Created by wpsimon09 on 24/04/24.
//

#ifndef PABLO_RENDERER_RENDERABLEBUILDER_H
#define PABLO_RENDERER_RENDERABLEBUILDER_H

#include "Renderer/Renderable/Renderable.h"
#include "Renderer/Enums/UIBuilderEnums.h"

class RenderableBuilder {
    static std::unique_ptr<Renderable> buildRenderable(GEOMETRY geomtry , MATERIAL material);
};


#endif //PABLO_RENDERER_RENDERABLEBUILDER_H
