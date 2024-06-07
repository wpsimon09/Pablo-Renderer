//
// Created by wpsimon09 on 05/06/24.
//

#include "AssetsManager.h"


std::shared_ptr<Texture2D> AssetsManager::loadSingleTexture(const char *path, bool toGL) {
    loadedTextures.insert(std::make_pair(path,std::make_shared<Texture2D>(path,true, toGL)));
    return loadedTextures.end()->second;
}

void AssetsManager::loadSingleTextureOnThread(const char *path, std::vector<std::shared_ptr<Texture2D>> &tempStorage) {
    std::lock_guard<std::mutex> lock(textureLock);
    tempStorage.push_back(std::make_shared<Texture2D>(path,true, false));
}

std::shared_ptr<Texture2D> AssetsManager::getTexture(const char *path) {
    auto tex = loadedTextures.find(path);
    if(tex != loadedTextures.end()){
        return tex->second;
    }else
        return loadSingleTexture(path, true);
}


std::vector<std::shared_ptr<Texture2D>> AssetsManager::getMultipleTextures(std::vector<const char *> paths) {
    std::vector<std::shared_ptr<Texture2D>> textures;
    std::vector<const char*> texturesToLoad;
    for (int i = 0; i < paths.size(); ++i) {
        auto possibleTexture = loadedTextures.find(paths[i]);
        if(possibleTexture != loadedTextures.end()){
            textures.emplace_back(possibleTexture->second);
            paths.erase(paths.begin()+i);
        }else{
            texturesToLoad.emplace_back(paths[i]);
        }
    }
    loadMultipleTextures(texturesToLoad);

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
    if(instance != nullptr){
        return this->instance;
    }else{
        instance = new AssetsManager();
        return instance;
    }
}

