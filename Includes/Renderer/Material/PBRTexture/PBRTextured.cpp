//
// Created by wpsimon09 on 31/12/23.
//

#include "PBRTextured.h"

PBRTextured::PBRTextured(bool supportsAreaLight, std::string pathToTheDirectory, bool isRelativePath,std::string shaderNamingConvention,
                         std::string fileFormat) : Material() {
    if (supportsAreaLight) {
        this->shader = ShaderManager::getShader(SHADER_AREA_LIGHT_TEXTURES);
    } else {
        this->shader = ShaderManager::getShader(SHADER_PBR_TEXTURED);
    }
    this->supportsIBL = true;
    this->supportsAreaLight = supportsAreaLight;
    this->hasEmissionTexture = false;

    this->material = std::make_unique<Texture2DArray>();

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

void PBRTextured::addTexture(std::unique_ptr<PBRMaterial<Texture2D>> texture) {
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

    if (ImGui::TreeNodeEx("Textures")) {
        for (auto &texture: this->textures) {
            if(texture->type != nullptr && texture != nullptr){

                        ImVec2 imageSize((float) texture->type->texWidth / 4, (float) texture->type->texHeight / 4);
                        if (ImGui::TreeNodeEx(texture->shaderName.c_str())) {
                            ImGui::BeginChild("##", imageSize);
                            ImGui::GetWindowDrawList()->AddImage(

                                    (void *) texture->type->ID,
                                    ImGui::GetCursorScreenPos(), // Use cursor screen position as top-left corner
                                    ImVec2(ImGui::GetCursorScreenPos().x + imageSize.x ,
                                           ImGui::GetCursorScreenPos().y + imageSize.y ), // Use bottom-right corner
                                    ImVec2(0, 1),
                                    ImVec2(1, 0)
                            );
                            ImGui::EndChild();
                            ImGui::TreePop();
                        }
                    }
            else
                ImGui::Text("Error::No texture loaded");

                }

                ImGui::TreePop();
            }

    ImGui::NewLine();
    ImGui::Checkbox("SupportsIBL", &this->supportsIBL);
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
            std::make_unique<PBRMaterial<Texture2D>>(nullptr, shaderNamingConvention + "albedoMap", 0));

    /***
    * @brief Roughness
    */
    fullPath = absolutePath + pathToTheDirectory + "/roughness" + fileFormat;
    pathsToLoad.push_back(fullPath);
    this->addTexture(
            std::make_unique<PBRMaterial<Texture2D>>(nullptr, shaderNamingConvention + "roughnessMap",
                                                     1));

    /***
    * @brief Metallic
    */
    fullPath = absolutePath + pathToTheDirectory + "/metallic" + fileFormat;
    pathsToLoad.push_back(fullPath);
    this->addTexture(
            std::make_unique<PBRMaterial<Texture2D>>(nullptr, shaderNamingConvention + "metallicMap",
                                                     2));

    /***
    * @brief Normal map
    */
    fullPath = absolutePath + pathToTheDirectory + "/normal" + fileFormat;
    pathsToLoad.push_back(fullPath);
    this->addTexture(
            std::make_unique<PBRMaterial<Texture2D>>(nullptr, shaderNamingConvention + "normalMap", 3));

    /***
     * @brief AO map
     */
    fullPath = absolutePath + pathToTheDirectory + "/ao" + fileFormat;
    pathsToLoad.push_back(fullPath);
    this->addTexture(
            std::make_unique<PBRMaterial<Texture2D>>(nullptr, shaderNamingConvention + "aoMap", 4));

    /***
     * @brief Depth map
     */
    fullPath = absolutePath + pathToTheDirectory + "/displacement" + fileFormat;
    pathsToLoad.push_back(fullPath);
    this->addTexture(
            std::make_unique<PBRMaterial<Texture2D>>(nullptr, shaderNamingConvention + "displacementMap",
                                                    5));
    /***
     * @brief Preform load
     */
    auto loadedTextures = assetsManagerInstance->getMultipleTextures(pathsToLoad);
    for(int i = 0; i<loadedTextures.size(); i++){
        textures[i]->type = loadedTextures[i];
    }
}











