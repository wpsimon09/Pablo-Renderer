//
// Created by wpsimon09 on 31/12/23.
//

#include "PBRTextured.h"

PBRTextured::PBRTextured(bool supportsAreaLight, std::string pathToTheDirectory, bool isRelativePath, std::string name, std::string shaderNamingConvention,
                         std::string fileFormat) : Material() {
    if (supportsAreaLight) {
        this->shader = ShaderManager::getShader(SHADER_AREA_LIGHT_TEXTURES);
    } else {
        this->shader = ShaderManager::getShader(SHADER_PBR_TEXTURED);
    }

    if(name.empty()) {
        this->name = "Textured material" + std::to_string(this->ID);
    }else {
        this->name = name;
    }
    
    this->supportsIBL = true;
    this->supportsAreaLight = supportsAreaLight;
    this->hasEmissionTexture = false;

    this->material = std::make_unique<Texture2DArray>();
    this->materialType = PBR_TEXTURE_MAPS;

    if (!pathToTheDirectory.empty()) {
        auto assetsManagerInstance = AssetsManager::getInstance();
        this->loadMaterials(assetsManagerInstance, pathToTheDirectory,isRelativePath,shaderNamingConvention, fileFormat);
    }

}

void PBRTextured::configureShader() {
    this->shader->use();
    this->shader->setFloat("hasEmission", this->hasEmissionTexture);
    this->shader->setFloat("supportsIBL", this->supportsIBL);
    for (auto &texture: this->textures) {
        if (texture != nullptr && texture->type != nullptr) {
            ShaderHelper::setTextureToShader(shader, *texture->type, texture->shaderName, texture->samplerID);
        }
    }
}

void PBRTextured::addTexture(std::shared_ptr<PBRMaterial<Texture2D>> texture) {
    if (texture != nullptr) {
        texture->samplerID = samplerCount;
        this->textures.push_back(std::move(texture));
        this->samplerCount++;
    }
}

std::shared_ptr<Texture2D> PBRTextured::getAlbedoTexture() {
    return this->textures[0]->type;
}

void PBRTextured::renderUI() {
    ImGui::Text(this->shader->name.c_str());
    PBRTexturedMaterialUI::display(this->textures);
    ImGui::NewLine();
    ImGui::Checkbox("SupportsIBL", &this->supportsIBL);
}

void PBRTextured::setAreaLightSupport(bool supportsAreaLight) {
    this->supportsAreaLight = supportsAreaLight;
    if (this->supportsAreaLight) {
        this->shader = ShaderManager::getShader(SHADER_AREA_LIGHT_TEXTURES);
    } else {
        this->shader = ShaderManager::getShader(SHADER_PBR_TEXTURED);
    }
}


std::vector<std::reference_wrapper<Texture2D>> PBRTextured::getTextures() {
    std::vector<std::reference_wrapper<Texture2D>> fetchedTextures;
    for (auto &texture: this->textures) {
        fetchedTextures.push_back(std::ref(*texture->type));
    }
    return fetchedTextures;
}

void PBRTextured::loadMaterials(AssetsManager* assetsManagerInstance,std::string pathToTheDirectory,bool isRelativePath, std::string shaderNamingConvention, std::string fileFormat) {
    std::string fullPath;
    this->textures.clear();
    /***
     * @brief Gather textures paths to laod
     */
    std::vector<std::string> pathsToLoad;

    /***
     * @brief Albedo map
     */
    auto absolutePath = isRelativePath ? PABLO_PATH : "";

    fullPath = absolutePath + pathToTheDirectory + "/albedo" + fileFormat;
    pathsToLoad.push_back(fullPath);
    this->addTexture(
            std::make_unique<PBRMaterial<Texture2D>>(nullptr, shaderNamingConvention + "albedoMap", 0, MATERIAL_ALBEDO));

    /**
     * Metalness, roughness, ao maps packed in one texture
     */
    fullPath = absolutePath + pathToTheDirectory + "/arm" + fileFormat;
    pathsToLoad.push_back(fullPath);
    this->addTexture(
            std::make_unique<PBRMaterial<Texture2D>>(nullptr, shaderNamingConvention + "armMap", 1, MATERIAL_ARM));

    /***
    * @brief Normal map
    */
    fullPath = absolutePath + pathToTheDirectory + "/normal" + fileFormat;
    pathsToLoad.push_back(fullPath);
    this->addTexture(
            std::make_unique<PBRMaterial<Texture2D>>(nullptr, shaderNamingConvention + "normalMap", 2, MATERIAL_NORMAL));


    /***
     * @brief Preform load
     */
    auto loadedTextures = assetsManagerInstance->getMultipleTextures(pathsToLoad);
    for(int i = 0; i<loadedTextures.size(); i++){
        if(loadedTextures[i]->wasFound) {
            textures[i]->type = loadedTextures[i];
            textures[i]->type->setTextureType(textures[i]->material_type);
        }
    }
}











