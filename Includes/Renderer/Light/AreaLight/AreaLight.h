//
// Created by wpsimon09 on 28/04/24.
//

#ifndef PABLO_RENDERER_AREALIGHT_H
#define PABLO_RENDERER_AREALIGHT_H

#include "Renderer/Light/Light.h"
#include "Renderer/Utils/Texture/Texture2D/Texture2D.h"
#include "Renderer/Geometry/Shapes/Plane/PlaneGeometry.h"
#include "Renderer/Material/BasicMaterialColor/BasicMaterialColor.h"

class AreaLight: public Light {
public:
    AreaLight(glm::vec3 position = glm::vec3(3.0f, 0.0f, -2.0f), glm::vec3 color = glm::vec3(20.0f, 20.0f, 20.0f));

    void update(std::shared_ptr<Shader> shader, bool isCastingShadows) override;

    void renderUi() override;

    void render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) override;

protected:
    void updateLightViewMatrix() override;

private:
    std::unique_ptr<Texture2D> LTC;
    std::unique_ptr<Texture2D> LTCInverse;

    std::unique_ptr<LightProperty<glm::vec3>>scale;
};


#endif //PABLO_RENDERER_AREALIGHT_H
