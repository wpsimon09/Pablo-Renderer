//
// Created by wpsimon09 on 30/12/23.
//

#ifndef CLIONTEST_MATERIAL_H
#define CLIONTEST_MATERIAL_H
#include "Shader.h"
#include "iostream"

template<typename T>
struct PBRMaterial{
    T type;
    std::string shaderName;
    PBRMaterial(T type, std::string shaderName){
        this->type = type;
        this->shaderName = shaderName;
    }
};

class Material {
public:
    Shader* shader;
    ~Material() = default;
    virtual void printLog() const{};
};


#endif //CLIONTEST_MATERIAL_H
