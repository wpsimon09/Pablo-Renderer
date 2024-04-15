//
// Created by wpsimon09 on 15/04/24.
//

#include "OrbitCamera.h"
#include "Renderer/Utils/GLFWHelper/GLFWHelper.h"


OrbitCamera::OrbitCamera(glm::vec3 center, glm::vec3 up, float radius, float minRadius, float azimuthAngle,
                         float polarAngle): Camera(center, up) {
    this->radius = radius;
    this->minRadius = minRadius;
    this->azimuthAngle = azimuthAngle;
    this->polarAngle = polarAngle;

    this->position = getEye();
}

void OrbitCamera::rotateAzimutn(float radians) {
    azimuthAngle += radians;
    const auto fullCircle = 2.0f * glm::pi<float>();
    azimuthAngle = fmodf(azimuthAngle, fullCircle);
    if(azimuthAngle<0.0f){
        azimuthAngle = azimuthAngle+fullCircle;
    }
    this->position = getEye();
}

void OrbitCamera::rotatePolar(float radains) {
    polarAngle += radains;

    const auto polarCap = glm::pi<float>() /2 - 0.001f;

    if (this->polarAngle > polarCap) {
        this->polarAngle = polarCap;
    }

    if (this->polarAngle < -polarCap) {
        this->polarAngle = -polarCap;
    }
    this->position = getEye();

}

void OrbitCamera::zoom(float by) {
    this->radius -= by;

    if(radius< minRadius){
        radius = minRadius;
    }
    this->position = getEye();
}

void OrbitCamera::moveHorizontal(float distance) {
    const auto pos = getEye();
    const glm::vec3 viewVector = glm::normalize(this->position - this->center);
    const glm::vec3 strafeVector = glm::normalize(glm::cross(viewVector, worldUp));
    center += worldUp + distance;
    this->position = getEye();
}

void OrbitCamera::moveVertical(float distance) {
    center+= worldUp + distance;
    this->position = getEye();

}

void OrbitCamera::processResize(int newWidht, int newHeight) {
    this->projection = glm::perspective(glm::radians(75.0f), (float)GLFWHelper::getScreenHeight() / (float)GLFWHelper::getScreenHeight(), 0.1f, 200.0f);
    this->position = getEye();
}

glm::vec3 OrbitCamera::getEye() {
    const auto sineAzimuth = sin(azimuthAngle);
    const auto cosineAzimuzh = cos(azimuthAngle);
    const auto sinePolar = sin(polarAngle);
    const auto cosinePolar = cos(polarAngle);

    const auto x = center.x + radius * cosinePolar * cosineAzimuzh;
    const auto y = center.y + radius * sinePolar;
    const auto z = center.z + radius * cosinePolar * sineAzimuth;

    return {x,y,z};
}


