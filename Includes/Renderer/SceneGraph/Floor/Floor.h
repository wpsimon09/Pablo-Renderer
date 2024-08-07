
//
// Created by wpsimon09 on 04/02/24.
//

#ifndef PABLO_RENDERER_FLOOR_H
#define PABLO_RENDERER_FLOOR_H

#include "Renderer/SceneGraph/SceneNode/SceneNode.h"
#include "Shader.h"
#include "Renderer/Geometry/Geometry.h"
#include "Renderer/Geometry/Shapes/Plane/PlaneGeometry.h"
#include "Renderer/Material/PBRTexture/PBRTextured.h"
class Floor : public SceneNode{
public:
    Floor();
private:
    std::shared_ptr<Shader> shader;
};


#endif //PABLO_RENDERER_FLOOR_H
