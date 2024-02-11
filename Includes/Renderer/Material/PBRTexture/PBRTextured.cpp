//
// Created by wpsimon09 on 31/12/23.
//

#include "PBRTextured.h"

PBRTextured::PBRTextured(Shader* shader, std::string pathToTheDirectory, std::string shaderNamingConvention, std::string fileFormat): Material(shader) {
        Texture2D albedo((pathToTheDirectory+"/albedo"+fileFormat).c_str(), true);
        this->textures.push_back(new PBRMaterial<Texture2D>(std::move(albedo), shaderNamingConvention+"albedoMap", 0));

        Texture2D rougness((pathToTheDirectory+"/roughness"+ fileFormat).c_str(), true);
        this->textures.push_back(new PBRMaterial<Texture2D>(std::move(rougness), shaderNamingConvention+"rougnessMap", 1));

        Texture2D metallic((pathToTheDirectory+"/metallic"+ fileFormat).c_str(), true);
        this->textures.push_back(new PBRMaterial<Texture2D>(std::move(metallic), shaderNamingConvention+"metallnesMap", 2));

        Texture2D normal((pathToTheDirectory+"/normal"+ fileFormat).c_str(), true);
        this->textures.push_back(new PBRMaterial<Texture2D>(std::move(normal), shaderNamingConvention+"normalMap", 3));

        Texture2D _ao((pathToTheDirectory + "/ao" + fileFormat).c_str(), true);
        this->textures.push_back(new PBRMaterial<Texture2D>(std::move(_ao), shaderNamingConvention + "aoMap", 4));

        Texture2D depthMap((pathToTheDirectory + "/displacement" + fileFormat).c_str(), true);
        this->textures.push_back(new PBRMaterial<Texture2D>(std::move(depthMap), shaderNamingConvention+"displacementMap", 5));
}

void PBRTextured::configureShader() {
    this->shader->use();
    for (auto &texture : this->textures) {
        if(texture->type.wasFound){
            this->shader->setInt(texture->shaderName, texture->samplerID);
            glActiveTexture(GL_TEXTURE0 + texture->samplerID);
            glBindTexture(GL_TEXTURE_2D, texture->type.ID);
        }
    }
}

PBRTextured::PBRTextured(Shader *shader, PBRMaterial<Texture2D> *baseColor, PBRMaterial<Texture2D> *normalMap,
                         PBRMaterial<Texture2D> *emmisionMap, PBRMaterial<Texture2D> *metalnessRougnessMap,
                         PBRMaterial<Texture2D> *rougness, PBRMaterial<Texture2D> *metalness,
                         PBRMaterial<Texture2D> *ao): Material(shader) {

    this->baseColor = baseColor;
    this->normalMap = normalMap;
    this->roughness = rougness;
    this->metalness = metalness;
    this->ao = ao;

    this->metallnesRougnessMap = metalnessRougnessMap;
    this->emmisionMap = emmisionMap;
}






