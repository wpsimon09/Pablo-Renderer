//
// Created by wpsimon09 on 15/04/24.
//

#ifndef PABLO_RENDERER_ORBITCAMERA_H
#define PABLO_RENDERER_ORBITCAMERA_H


#include "Renderer/Utils/Camera/Camera.h"

class OrbitCamera:public Camera {
public:
    explicit OrbitCamera(glm::vec3 center=glm::vec3(0.0f, 0.0f, 0.0f) ,glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float radius = 40.0f, float minRadius = 1.0f, float azimuthAngle = -10.0f, float polarAngle = 10.0f);

    void rotateAzimutn(float radians);

    void rotatePolar(float radains);

    void zoom(float by);

    void moveHorizontal(float distance);

    void moveVertical(float distance);

    void processResize(int newWidht, int newHeight) override;

private:
    glm::vec3 getEye() override;

    float radius;
    float minRadius;
    float azimuthAngle;
    float polarAngle;
};

#endif //PABLO_RENDERER_ORBITCAMERA_H
