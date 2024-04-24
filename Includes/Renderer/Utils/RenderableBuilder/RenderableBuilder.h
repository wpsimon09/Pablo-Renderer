//
// Created by wpsimon09 on 24/04/24.
//

#ifndef PABLO_RENDERER_RENDERABLEBUILDER_H
#define PABLO_RENDERER_RENDERABLEBUILDER_H

#include "Renderer/Renderable/Renderable.h"
#include "Renderer/Enums/UIBuilderEnums.h"
#include "Renderer/Geometry/Shapes/Sphere/SphereGeometry.h"
#include "Renderer/Geometry/Shapes/Plane/PlaneGeometry.h"
#include "Renderer/SceneGraph/ModelSceneNode/ModelSceneNode.h"

class RenderableBuilder {
public:
    inline static GEOMETRY selectedGeometry = CUBE;
    inline static MATERIAL selectedMateial = TEXTURE;

    inline static std::string modelOath;

    inline static glm::vec3 color;
    inline static std::string textureDirectory;
    inline static bool castsShadow;
    inline static bool supportsIBL;
    inline static bool keepModelMaterial = false;
    inline static char text[32] = "";

    static std::unique_ptr<Renderable> buildRenderable();
};


#endif //PABLO_RENDERER_RENDERABLEBUILDER_H
