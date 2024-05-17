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



