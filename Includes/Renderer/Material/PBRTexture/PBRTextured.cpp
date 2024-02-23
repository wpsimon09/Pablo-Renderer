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
    this->textures.push_back(std::make_unique<PBRMaterial<Texture2D>>(std::move(texture), shaderNamingConvention + "albedoMap", 0));

    // Roughness map
    fullPath = pathToTheDirectory + "/roughness" + fileFormat;
    texture = std::make_unique<Texture2D>(fullPath.c_str(), true);
    this->textures.push_back(std::make_unique<PBRMaterial<Texture2D>>(std::move(texture), shaderNamingConvention + "roughnessMap", 1));

    // Metallic map
    fullPath = pathToTheDirectory + "/metallic" + fileFormat;
    texture = std::make_unique<Texture2D>(fullPath.c_str(), true);
    this->textures.push_back(std::make_unique<PBRMaterial<Texture2D>>(std::move(texture), shaderNamingConvention + "metallicMap", 2));

    // Normal map
    fullPath = pathToTheDirectory + "/normal" + fileFormat;
    texture = std::make_unique<Texture2D>(fullPath.c_str(), true);
    this->textures.push_back(std::make_unique<PBRMaterial<Texture2D>>(std::move(texture), shaderNamingConvention + "normalMap", 3));

    // Ambient Occlusion map
    fullPath = pathToTheDirectory + "/ao" + fileFormat;
    texture = std::make_unique<Texture2D>(fullPath.c_str(), true);
    this->textures.push_back(std::make_unique<PBRMaterial<Texture2D>>(std::move(texture), shaderNamingConvention + "aoMap", 4));

    // Depth map
    fullPath = pathToTheDirectory + "/displacement" + fileFormat;
    texture = std::make_unique<Texture2D>(fullPath.c_str(), true);
    this->textures.push_back(std::make_unique<PBRMaterial<Texture2D>>(std::move(texture), shaderNamingConvention + "displacementMap", 5));

}

void PBRTextured::configureShader() {

    for (auto &texture : this->textures) {
        if(texture != nullptr ){
            this->shader->use();
            this->shader->setInt(texture->shaderName, texture->samplerID);
            glActiveTexture(GL_TEXTURE0 + texture->samplerID);
            glBindTexture(GL_TEXTURE_2D, texture->type->ID);
        }
    }
}

void PBRTextured::addTexture(std::unique_ptr<PBRMaterial<Texture2D>> texture) {
    this->textures.push_back(std::move(texture));
}


PBRTextured::PBRTextured(std::shared_ptr<Shader> shader) : Material(std::move(shader)) {
}







