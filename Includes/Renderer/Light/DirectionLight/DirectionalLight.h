//
// Created by wpsimon09 on 28/04/24.
//

#ifndef PABLO_RENDERER_DIRECTIONALLIGHT_H
#define PABLO_RENDERER_DIRECTIONALLIGHT_H

#include "Renderer/Light/Light.h"

class DirectionalLight: public Light {
public:
    DirectionalLight(glm::vec3 color = glm::vec3(20.0f, 20.0f, 20.2f), glm::vec3 position = glm::vec3(0.0f, 3.0f, 3.0f));

    /**
     * Updates the shader that is using given light
     * @param shader shader that is using this light
     * @param isCastingShadows is the object casting shadow
     */
    void update(std::shared_ptr<Shader> shader, bool isCastingShadows) override;

    void render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) override;

    void renderUi() override;

protected:
    void updateLightViewMatrix() override;
};


#endif //PABLO_RENDERER_DIRECTIONALLIGHT_H
