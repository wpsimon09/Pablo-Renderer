//
// Created by wpsimon09 on 15/04/24.
//

#ifndef PABLO_RENDERER_CAMERA_H
#define PABLO_RENDERER_CAMERA_H

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Shader.h"
#include "memory"

class Camera {
public:
    Camera(glm::vec3 center, glm::vec3 up);

    glm::mat4 getPojectionMatix();

    glm::mat4 getViewMatrix();

    glm::vec3 getPosition();

    void update(std::shared_ptr<Shader> shader);

    virtual void processResize(int newWidht, int newHeight){};
protected:
    virtual glm::vec3 getEye(){return glm::vec3(1.0f);};

    glm::vec3 position;
    glm::vec3 center;
    glm::vec3 worldUp;

    glm::mat4 projection = glm::mat4(1.0f);
};


#endif //PABLO_RENDERER_CAMERA_H
