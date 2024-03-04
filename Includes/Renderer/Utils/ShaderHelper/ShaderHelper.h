//
// Created by wpsimon09 on 12/01/24.
//

#ifndef PABLO_RENDERER_SHADERHELPER_H
#define PABLO_RENDERER_SHADERHELPER_H

#include "Shader.h"
#include "Renderer/Utils/Texture/TextureBase.h"
#include "Debug/DebugLogger.h"
#include "memory"
class ShaderHelper {
public:
    static void setTransfomrationMatrices(std::shared_ptr<Shader> shader, glm::mat4 model = glm::mat4(1.0f),
                                          glm::mat4 view = glm::mat4(1.0f), glm::mat4 projection = glm::mat4(1.0f));

    static void setTextureToShader(std::shared_ptr<Shader> shader, const TextureBase& texture, std::string shaderName);

    static void setTextureToShader(std::shared_ptr<Shader> shader, const TextureBase& texture, std::string shaderName, int samplerID);

};
#endif //PABLO_RENDERER_SHADERHELPER_H
