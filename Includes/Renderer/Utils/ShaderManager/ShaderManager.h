//
// Created by wpsimon09 on 17/05/24.
//

#ifndef PABLO_RENDERER_SHADERMANAGER_H
#define PABLO_RENDERER_SHADERMANAGER_H

#include "map"
#include "Renderer/Enums/ShaderTypes.h"
#include "Shader.h"
#include "memory"

class ShaderManager {
public:
    static ShaderManager* getInstance();

private:
    std::map<ShaderType,std::shared_ptr<Shader>> shaders;

    inline static ShaderManager* instance = nullptr;
};


#endif //PABLO_RENDERER_SHADERMANAGER_H
