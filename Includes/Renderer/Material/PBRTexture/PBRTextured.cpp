//
// Created by wpsimon09 on 31/12/23.
//

#include "PBRTextured.h"

PBRTextured::PBRTextured(std::string pathToTheDirectory,bool supportsIBL, std::string shaderNamingConvention, std::string fileFormat): Material() {
    std::string fullPath;
    std::unique_ptr<Texture2D> texture;
    if(supportsIBL){
        this->shader = std::make_shared<Shader>("VertexShader/PBR/PBRVertex.glsl","FragmentShader/PBR/PBR-IBL-Textured-Fragment.glsl", "PBR-IBL-Shader");
    }else
        this->shader = std::make_shared<Shader>("VertexShader/PBR/PBRVertex.glsl","FragmentShader/PBR/PBR-Textured-Fragment.glsl", "PBR-Shader");
    this->shader->supportsIBL = supportsIBL;
    this->supportsIBL = supportsIBL;

    // Albedo map
    fullPath = pathToTheDirectory + "/albedo" + fileFormat;
    texture = std::make_unique<Texture2D>(fullPath.c_str(), true);
    this->addTexture(std::make_unique<PBRMaterial<Texture2D>>(std::move(texture), shaderNamingConvention + "albedoMap", 0));

    // Roughness map
    fullPath = pathToTheDirectory + "/roughness" + fileFormat;
    texture = std::make_unique<Texture2D>(fullPath.c_str(), true);
    this->addTexture(std::make_unique<PBRMaterial<Texture2D>>(std::move(texture), shaderNamingConvention + "roughnessMap", 1));

    // Metallic map
    fullPath = pathToTheDirectory + "/metallic" + fileFormat;
    texture = std::make_unique<Texture2D>(fullPath.c_str(), true);
    this->addTexture(std::make_unique<PBRMaterial<Texture2D>>(std::move(texture), shaderNamingConvention + "metallicMap", 2));

    // Normal map
    fullPath = pathToTheDirectory + "/normal" + fileFormat;
    texture = std::make_unique<Texture2D>(fullPath.c_str(), true);
    this->addTexture(std::make_unique<PBRMaterial<Texture2D>>(std::move(texture), shaderNamingConvention + "normalMap", 3));

    // Ambient Occlusion map
    fullPath = pathToTheDirectory + "/ao" + fileFormat;
    texture = std::make_unique<Texture2D>(fullPath.c_str(), true);
    this->addTexture(std::make_unique<PBRMaterial<Texture2D>>(std::move(texture), shaderNamingConvention + "aoMap", 4));

    // Depth map
    fullPath = pathToTheDirectory + "/displacement" + fileFormat;
    texture = std::make_unique<Texture2D>(fullPath.c_str(), true);
    this->addTexture(std::make_unique<PBRMaterial<Texture2D>>(std::move(texture), shaderNamingConvention + "displacementMap", 5));

    this->hasEmissionTexture = false;
}

void PBRTextured::configureShader() {
    this->shader->use();
    this->shader->setFloat("hasEmission", this->hasEmissionTexture);
    for (auto &texture : this->textures) {
        if(texture != nullptr){
            ShaderHelper::setTextureToShader(shader, *texture->type, texture->shaderName, texture->samplerID);
        }
    }
}

void PBRTextured::addTexture(std::unique_ptr<PBRMaterial<Texture2D>> texture) {
    if(texture != nullptr){
        texture->samplerID = samplerCount;
        this->textures.push_back(std::move(texture));
        this->samplerCount ++;
    }
}


PBRTextured::PBRTextured(bool supportsIBL) : Material() {
    this->shader = std::make_shared<Shader>("VertexShader/PBR/PBRVertex.glsl","FragmentShader/PBR/PBR-IBL-Textured-Fragment.glsl", "PBR-IBL-Shader");
    this->shader->supportsIBL = supportsIBL;
    this->supportsIBL = supportsIBL;
}

std::shared_ptr<Texture2D> PBRTextured::getAlbedoTexture() {
    return this->textures[0]->type;
}








