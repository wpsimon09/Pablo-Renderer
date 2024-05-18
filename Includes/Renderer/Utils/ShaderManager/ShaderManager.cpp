//
// Created by wpsimon09 on 17/05/24.
//

#include "ShaderManager.h"

ShaderManager::ShaderManager() {

}

ShaderManager *ShaderManager::getInstance() {
    if(ShaderManager::instance == nullptr){
        return new ShaderManager();
    }else{
        return ShaderManager::instance;
    }
}

std::shared_ptr<Shader> ShaderManager::getShader(ShaderType type) {
    if(compiledShaders.contains(type)){
        return compiledShaders.find(type)->second;
    }else{
        std::shared_ptr<Shader> newShader;
        for(auto &shader: __uncompiledShaders){
            if(shader.type == type){
                newShader = std::make_shared<Shader>(shader.vertexPath.c_str(), shader.fragmentPath.c_str(), shader.name);
                compiledShaders.insert(std::make_pair(type,std::move(newShader)));
                break;
            }
        }
        return compiledShaders.find(type)->second;
    }
}



