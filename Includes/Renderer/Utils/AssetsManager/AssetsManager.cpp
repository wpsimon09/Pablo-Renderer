//
// Created by wpsimon09 on 05/06/24.
//

#include "AssetsManager.h"


std::shared_ptr<Texture2D> AssetsManager::loadSingleTexture(const char *path, bool toGL) {
    auto newTexture =  std::make_shared<Texture2D>(path, true, toGL);
    if(newTexture->wasFound);
        loadedTextures.insert(std::make_pair(path,newTexture));
    return newTexture;
}

void AssetsManager::loadSingleTextureOnThread(const char *path, std::vector<std::shared_ptr<Texture2D>> &tempStorage) {
    std::lock_guard<std::mutex> lock(textureLock);
    tempStorage.push_back(std::make_shared<Texture2D>(path,true, false));
}

std::shared_ptr<Texture2D> AssetsManager::getTexture(std::string path) {
    auto tex = loadedTextures.find(path);
    if(tex != loadedTextures.end()){
        return tex->second;
    }else
        return loadSingleTexture(path.c_str(), true);
}


std::shared_ptr<Texture2D> AssetsManager::getTextureOnThread(std::string path) {
    auto tex = loadedTextures.find(path);
    if(tex != loadedTextures.end()){
        return tex->second;
    }else{
        std::lock_guard<std::mutex> lock(textureLock);
        auto newTexture = std::make_shared<Texture2D>(path.c_str(),true, false);
        loadedTextures.insert(std::make_pair(path, newTexture));
        return newTexture;
    }
}

std::vector<std::shared_ptr<Texture2D>> AssetsManager::getMultipleTextures(std::vector<std::string> paths) {
    std::vector<std::shared_ptr<Texture2D>> textures;
    std::vector<const char*> texturesToLoad;
    
    /***
     * @brief Find what textures are already loaded and which needs to be loaded 
     */
    for (auto & path : paths) {
        auto possibleTexture = loadedTextures.find(path);
        if(possibleTexture != loadedTextures.end()){
            textures.emplace_back(possibleTexture->second);
        }else{
            texturesToLoad.emplace_back(path.c_str());
        }
    }

    auto newTextures = loadMultipleTextures(texturesToLoad);

    textures.insert(textures.end(), newTextures.begin(), newTextures.end());

    return textures;
}

std::vector<std::shared_ptr<Texture2D>> AssetsManager::loadMultipleTextures(std::vector<const char *> texturePaths) {
    std::vector<std::thread> threads;
    std::vector<std::shared_ptr<Texture2D>> textures;

    for(auto &path: texturePaths){
        threads.emplace_back(&AssetsManager::loadSingleTextureOnThread,path, std::ref(textures));
    }

    for(auto &thread: threads){
        thread.join();
    }

    for (auto &texture: textures) {
        texture->passToOpenGL();
        auto path = texture->getFullPath();
        loadedTextures.insert(std::make_pair(path, texture));
    }

    return textures;
}

AssetsManager *AssetsManager::getInstance() {
    if(AssetsManager::instance != nullptr){
        return AssetsManager::instance;
    }else{
        AssetsManager::instance = new AssetsManager();
        return AssetsManager::instance;
    }
}

void AssetsManager::loadTexturesToOpenGL() {
    for(auto &texture: loadedTextures){
        if(texture.second->isInGL){
            texture.second->passToOpenGL();
        }else
            continue;
    }
}

void AssetsManager::storeMaterial(std::shared_ptr<Material> newMaterial) {
    if(!this->loadedMaterials.contains(newMaterial->getID())) {
        this->loadedMaterials.insert(std::make_pair(newMaterial->getID(), newMaterial));
    }
}

void AssetsManager::storeTexture(std::shared_ptr<Texture2D> newTexture) {
    if(!loadedTextures.contains(newTexture->getFullPath())) {
        loadedTextures.insert(std::make_pair(newTexture->getFullPath(), std::move(newTexture)));
    }
}

const std::vector<std::shared_ptr<Texture2D>> AssetsManager::getLoadedTextures(MATERIAL_TEXTURE_TYPE filter) {
    std::vector<std::shared_ptr<Texture2D>> second;

    for (auto texture : loadedTextures) {
        if(texture.second->getMaterialTextureType() == filter || filter == UNDEFINED)
            second.emplace_back(texture.second);
    }

    return second;
}

std::vector<std::shared_ptr<Material>> AssetsManager::getExistingMaterisl(MATERIAL materialType) {
    std::vector<std::shared_ptr<Material>> second;

    for (auto material : loadedMaterials) {
        if(materialType == ALL || materialType == material.second->getType())
            second.emplace_back(material.second);
    }

    return second;
}

std::shared_ptr<Material> AssetsManager::getMaterialByAlbedoTexture(std::string fileName) {
    for(auto &material: loadedMaterials) {
        if(material.second->getAlbedoTexture()->getFileName() == fileName) {
            return material.second;
        }
    }
    return nullptr;
}

std::shared_ptr<Material> AssetsManager::getMaterialByAssimpIndex(unsigned int assimpIndex) {
    for(auto material: loadedMaterials) {
        if(material.second->getAssimpIndex() == assimpIndex) {
            return material.second;
        }
    }
    return nullptr;
}




