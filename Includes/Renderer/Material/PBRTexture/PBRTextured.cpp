//
// Created by wpsimon09 on 31/12/23.
//

#include "PBRTextured.h"

PBRTextured::PBRTextured(bool supportsAreaLight,std::string pathToTheDirectory, std::string shaderNamingConvention, std::string fileFormat): Material() {
    std::string fullPath;
    std::unique_ptr<Texture2D> texture;
    if(supportsAreaLight){
        this->shader = ShaderManager::getShader(SHADER_AREA_LIGHT_TEXTURES);
    }else{
        this->shader = ShaderManager::getShader(SHADER_PBR_TEXTURED);
    }
    this->supportsIBL = true;
    this->supportsAreaLight = supportsAreaLight;
    this->hasEmissionTexture = false;

    if(!pathToTheDirectory.empty()){
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

}

void PBRTextured::configureShader() {
    this->shader->use();
    this->shader->setFloat("hasEmission", this->hasEmissionTexture);
    this->shader->setFloat("supportsIBL", this->supportsIBL);
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

std::shared_ptr<Texture2D> PBRTextured::getAlbedoTexture() {
    return this->textures[0]->type;
}

void PBRTextured::renderUI() {
    ImVec2 imageSize((float)this->getAlbedoTexture()->texWidth/4, (float)this->getAlbedoTexture()->texHeight/4);

    if(ImGui::TreeNodeEx("Textures")){
        ImGui::Text("Albedo");
        ImGui::GetWindowDrawList()->AddImage(

                (void *)this->getAlbedoTexture()->ID,
                ImGui::GetCursorScreenPos(), // Use cursor screen position as top-left corner
                ImVec2(ImGui::GetCursorScreenPos().x + imageSize.x/4, ImGui::GetCursorScreenPos().y + imageSize.y/4), // Use bottom-right corner
                ImVec2(0, 1),
                ImVec2(1, 0)
        );

        ImGui::TreePop();
    }

    ImGui::NewLine();
    ImGui::Checkbox("SupportsIBL",&this->supportsIBL);
}

std::vector<std::reference_wrapper<Texture2D>> PBRTextured::getTextures() {
    std::vector<std::reference_wrapper<Texture2D>> fetchedTextures;
    for(auto &texture : this->textures ){
        fetchedTextures.push_back(std::ref(*texture->type));
    }
    return fetchedTextures;
}









