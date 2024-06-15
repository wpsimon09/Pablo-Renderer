//
// Created by wpsimon09 on 02/06/24.
//

#ifndef PABLO_RENDERER_MATERIALSTOPROCESS_H
#define PABLO_RENDERER_MATERIALSTOPROCESS_H
#include "assimp/scene.h"
#include "vector"

struct MaterialToProcess{
    aiTextureType textureType;
    std::string shaderName;
    int samplerNumber;

    MaterialToProcess(aiTextureType type, std::string shaderName, int samplerID){
        this->textureType= type;
        this->shaderName = shaderName;
        this->samplerNumber = samplerID;
    }
};

const std::vector<MaterialToProcess> materialsToLoad = {
        MaterialToProcess(aiTextureType_DIFFUSE, "_albedoMap", 0),
    //    MaterialToProcess(aiTextureType_DIFFUSE_ROUGHNESS, "_rougnessMap", 1),
  //      MaterialToProcess(aiTextureType_METALNESS, "_metalnessMap", 2),
        MaterialToProcess(aiTextureType_NORMALS, "_normalMap", 1),
        MaterialToProcess(aiTextureType_AMBIENT_OCCLUSION, "_aoMap", 2),
        MaterialToProcess(aiTextureType_EMISSIVE, "_emmisionMap", 3),
        MaterialToProcess(aiTextureType_UNKNOWN, "_rougnessMetalnessMap", 4)
};

#endif //PABLO_RENDERER_MATERIALSTOPROCESS_H
