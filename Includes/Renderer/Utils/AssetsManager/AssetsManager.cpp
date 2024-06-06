//
// Created by wpsimon09 on 05/06/24.
//

#include <cstring>
#include "AssetsManager.h"


std::shared_ptr<Texture2D> AssetsManager::loadSingleTexture(const char *path, bool toGL) {
    return std::make_shared<Texture2D>(path,true, toGL);
}

void AssetsManager::loadSingleTextureOnThread(const char *path, std::vector<std::shared_ptr<Texture2D>> &tempStorage) {
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
    std::vector<std::shared_ptr<Texture2D>> texs;

    for (auto &path: paths) {
        texs.push_back(getTexture(path));
    }

    return texs;
}

void AssetsManager::loadMultipleTextures(std::vector<const char *> texturePaths) {
    std::vector<std::thread> threads;
    std::vector<std::shared_ptr<Texture2D>> textures;

    for(auto &path: texturePaths){
        threads.emplace_back(&AssetsManager::loadSingleTextureOnThread,path, &textures);
    }

    for(auto &thread: threads){
        thread.join();
    }
}

AssetsManager *AssetsManager::getInstance() {
    if(instance != nullptr){
        return this->instance;
    }else{
        instance = new AssetsManager();
        return instance;
    }
}

