//
// Created by wpsimon09 on 05/06/24.
//

#include "AssetsManager.h"


std::shared_ptr<Texture2D> AssetsManager::loadSingleTexture(const char *path, bool toGL) {
    auto newTexture =  std::make_shared<Texture2D>(path, true, toGL);
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
        loadedTextures.insert(std::make_pair(texture->getFullPath().c_str(), texture));
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

