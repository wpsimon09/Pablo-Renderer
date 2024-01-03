//
// Created by wpsimon09 on 03/01/24.
//

#include "BasicMaterialTextured.h"

BasicMaterialTextured::BasicMaterialTextured(Shader *shader, const char *path) {
    this->shader = shader;
    this->texture = new Texture2D(path);
}
