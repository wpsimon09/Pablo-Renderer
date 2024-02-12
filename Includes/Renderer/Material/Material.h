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
    int samplerID;
    PBRMaterial(T type, std::string shaderName,int samplerid = 0){
        this->type = std::move(type);
        this->shaderName = shaderName;
        this->samplerID = samplerid;
    }
};

class Material {
public:
    Shader* shader;
    Material() = default;
    Material(Shader *shader) {
        this->shader = shader;
    }
    virtual void configureShader(){};
    ~Material() = default;
    virtual void printLog() const{};
};


#endif //CLIONTEST_MATERIAL_H
