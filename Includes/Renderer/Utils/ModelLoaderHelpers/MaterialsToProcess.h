//
// Created by wpsimon09 on 02/06/24.
//

#ifndef PABLO_RENDERER_MATERIALSTOPROCESS_H
#define PABLO_RENDERER_MATERIALSTOPROCESS_H
#include "assimp/scene.h"
#include "vector"
#include "Renderer/Enums/MaterialTextureType.h"

struct MaterialToProcess{
    aiTextureType textureType;
    std::string shaderName;
    int samplerNumber;
    MATERIAL_TEXTURE_TYPE material_texture_type;

    MaterialToProcess(aiTextureType type, std::string shaderName, int samplerID, MATERIAL_TEXTURE_TYPE material_texture){
        this->textureType= type;
        this->shaderName = shaderName;
        this->samplerNumber = samplerID;
        this->material_texture_type = material_texture;
    }
};

const std::vector<MaterialToProcess> materialsToLoad = {
        MaterialToProcess(aiTextureType_DIFFUSE, "_albedoMap", 0, MATERIAL_ALBEDO),
    //    MaterialToProcess(aiTextureType_DIFFUSE_ROUGHNESS, "_rougnessMap", 1),
  //      MaterialToProcess(aiTextureType_METALNESS, "_metalnessMap", 2),
        MaterialToProcess(aiTextureType_NORMALS, "_normalMap", 1, MATERIAL_NORMAL),
        MaterialToProcess(aiTextureType_AMBIENT_OCCLUSION, "_aoMap", 2, MATERIAL_AMBIENT_OCCLUSION ),
        MaterialToProcess(aiTextureType_EMISSIVE, "_emmisionMap", 3, MATERIAL_EMMISION),
        MaterialToProcess(aiTextureType_UNKNOWN, "_rougnessMetalnessMap", 4, MATERIAL_ARM)
};

#endif //PABLO_RENDERER_MATERIALSTOPROCESS_H
