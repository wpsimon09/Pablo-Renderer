//
// Created by wpsimon09 on 12/01/24.
//

#ifndef PABLO_RENDERER_SHADERHELPER_H
#define PABLO_RENDERER_SHADERHELPER_H

#include "Shader.h"

class ShaderHelper {
public:
    static void setTransfomrationMatrices(Shader *shader, glm::mat4 model = glm::mat4(1.0f), glm::mat4 view = glm::mat4(1.0f) , glm::mat4 projection = glm::mat4(1.0f));
};


#endif //PABLO_RENDERER_SHADERHELPER_H
