//
// Created by wpsimon09 on 02/06/24.
//

#ifndef PABLO_RENDERER_MATERIALSTOPROCESS_H
#define PABLO_RENDERER_MATERIALSTOPROCESS_H
#include "assimp/scene.h"
#include "vector"

struct MaterialsToLoad{
    aiTextureType textureType;
    std::string shaderName;
    int samplerNumber;

    MaterialsToLoad(aiTextureType type, std::string shaderName, int samplerID){
        textureType= type;
        shaderName = shaderName;
        samplerNumber = samplerID;
    }
};

const std::vector<MaterialsToLoad> materialsToLoad = {
        MaterialsToLoad(aiTextureType_DIFFUSE, "_albedoMap", 0),
        MaterialsToLoad(aiTextureType_DIFFUSE_ROUGHNESS, "_rougnessMap", 1),
        MaterialsToLoad(aiTextureType_METALNESS, "_metalnessMap", 2),
        MaterialsToLoad(aiTextureType_NORMALS, "_normalMap", 3),
        MaterialsToLoad(aiTextureType_AMBIENT_OCCLUSION, "_aoMap", 4),
        MaterialsToLoad(aiTextureType_EMISSIVE, "_emmisionMap", 5),
        MaterialsToLoad(aiTextureType_UNKNOWN, "_rougnessMetalnessMap", 6)
};

#endif //PABLO_RENDERER_MATERIALSTOPROCESS_H
