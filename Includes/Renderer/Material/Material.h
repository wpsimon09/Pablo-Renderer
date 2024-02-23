//
// Created by wpsimon09 on 30/12/23.
//

#ifndef CLIONTEST_MATERIAL_H
#define CLIONTEST_MATERIAL_H
#include <utility>

#include "Shader.h"
#include "iostream"
#include "memory"

template<typename T>
struct PBRMaterial{
    std::shared_ptr<T> type;
    std::string shaderName;
    int samplerID;
    PBRMaterial(std::shared_ptr<T> type, std::string shaderName,int samplerid = 0){
        this->type = std::move(type);
        this->shaderName = shaderName;
        this->samplerID = samplerid;
    }

    PBRMaterial(T type, std::string shaderName,int samplerid = 0){
        this->type = std::make_unique<T>(std::move(type));
        this->shaderName = shaderName;
        this->samplerID = samplerid;
    }
};

class Material {
public:
    std::shared_ptr<Shader> shader;

    Material() = default;
    explicit Material(std::shared_ptr<Shader> shader) {
        this->shader = std::move(shader);
    }
    virtual void configureShader(){};
    ~Material() = default;
    virtual void printLog() const{};
};


#endif //CLIONTEST_MATERIAL_H
