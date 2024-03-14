//
// Created by wpsimon09 on 31/12/23.
//

#include "PBRTextured.h"

PBRTextured::PBRTextured(std::shared_ptr<Shader> shader, std::string pathToTheDirectory, std::string shaderNamingConvention, std::string fileFormat): Material(std::move(shader)) {
    std::string fullPath;
    std::unique_ptr<Texture2D> texture;

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

}

void PBRTextured::configureShader() {
    for (auto &texture : this->textures) {
        if(texture != nullptr){
            ShaderHelper::setTextureToShader(shader, *texture->type, texture->shaderName, texture->samplerID);
        }
    }
}

void PBRTextured::addTexture(std::unique_ptr<PBRMaterial<Texture2D>> texture) {
    this->textures.push_back(std::move(texture));
    this->samplerCount ++;
}


PBRTextured::PBRTextured(std::shared_ptr<Shader> shader) : Material(std::move(shader)) {
}








