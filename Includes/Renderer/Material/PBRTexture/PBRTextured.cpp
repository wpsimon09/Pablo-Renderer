//
// Created by wpsimon09 on 31/12/23.
//

#include "PBRTextured.h"

PBRTextured::PBRTextured(Shader* shader, std::string pathToTheDirectory, std::string shaderNamingConvention, std::string fileFormat): Material(shader) {
        this->shader = shader;

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

    for (auto &texture : this->textures) {
        if(texture != nullptr ){
            this->shader->use();
            this->shader->setInt(texture->shaderName, texture->samplerID);
            glActiveTexture(GL_TEXTURE0 + texture->samplerID);
            glBindTexture(GL_TEXTURE_2D, texture->type.ID);
        }
    }
}

void PBRTextured::addTexture(PBRMaterial<Texture2D> *texture) {
    this->textures.push_back(texture);
}


PBRTextured::PBRTextured(Shader *shader) : Material(shader) {
    this->shader = std::move(shader);
}







