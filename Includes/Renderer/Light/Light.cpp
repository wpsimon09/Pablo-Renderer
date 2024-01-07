//
// Created by wpsimon09 on 06/01/24.
//

#include "Light.h"

Light::Light(glm::vec3 position, glm::vec3 color) {
    this->position = new LightProperty(position, "lightPos");
    this->color = new LightProperty(position, "diffuseColor");
}
