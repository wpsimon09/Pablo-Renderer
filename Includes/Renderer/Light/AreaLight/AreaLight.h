//
// Created by wpsimon09 on 28/04/24.
//

#ifndef PABLO_RENDERER_AREALIGHT_H
#define PABLO_RENDERER_AREALIGHT_H

#include "Renderer/Light/Light.h"
#include "Renderer/Utils/Texture/Texture2D/Texture2D.h"
#include "Renderer/Geometry/Shapes/Plane/PlaneGeometry.h"
#include "Renderer/Material/BasicMaterialColor/BasicMaterialColor.h"
#include "ltc_matrix.h"

class AreaLight: public Light {
private:
    std::unique_ptr<Texture2D> LTC;
public:
    void update(std::shared_ptr<Shader> shader, bool isCastingShadows) override;

    void render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) override;

protected:
    void updateLightViewMatrix() override;

private:
    std::unique_ptr<Texture2D> LTCInverse;
public:
    AreaLight(glm::vec3 position, glm::vec3 color);
};


#endif //PABLO_RENDERER_AREALIGHT_H
