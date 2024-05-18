//
// Created by wpsimon09 on 17/05/24.
//

#ifndef PABLO_RENDERER_SHADERMANAGER_H
#define PABLO_RENDERER_SHADERMANAGER_H

#include <utility>

#include "iostream"
#include "UncompiledShaders.h"
#include "vector"
#include "map"
#include "algorithm"
#include "memory"
#include "Shader.h"

class ShaderManager {
public:
    static ShaderManager* getInstance();

private:
    ShaderManager();
    std::map<ShaderType,std::shared_ptr<Shader>> compiledShaders;
    std::shared_ptr<Shader> getShader(ShaderType type);
    inline static ShaderManager* instance = nullptr;
};


#endif //PABLO_RENDERER_SHADERMANAGER_H
