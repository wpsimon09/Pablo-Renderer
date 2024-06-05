//
// Created by wpsimon09 on 05/06/24.
//

#include <cstring>
#include "AssetsManager.h"


AssetsManager *AssetsManager::getInstance() {
    if(instance != nullptr){
        return instance;
    }else{
        instance = new AssetsManager();
        return  instance;
    }
}

std::vector<std::reference_wrapper<Texture2D>> AssetsManager::getMultipleTextures(std::vector<int> indexes) {
    std::vector<std::reference_wrapper<Texture2D>> texs;

    for (int &index: indexes) {
        texs.push_back(getTexture(index));
    }

    return texs;
}

std::reference_wrapper<Texture2D> AssetsManager::getTexture(int index) {
    auto tex = loadedTextures.find(index);
    if(tex != loadedTextures.end()){
        return std::ref(*tex->second);
    }else
        throw std::runtime_error("Texture not found in loaded textures");
}

void AssetsManager::loadSingleTexture(const char *path, bool toGL) {
    for(auto &loadedTexture: loadedTextures){
        if(std::strcmp(path, loadedTexture.second->getFullPath().c_str()) == 0||
           std::strcmp(path, loadedTexture.second->relativePath.c_str()) == 0 ){
            return;
        }
    }
    auto texture = std::make_unique<Texture2D>(path,true, toGL);
    loadedTextures.insert(std::make_pair(texturesCount,std::move(texture)));
    texturesCount++;
}

void AssetsManager::loadMultipleTexutres(std::vector<const char *> texturePaths) {
    std::vector<std::thread> threads;

    for(auto &path: texturePaths){
        threads.emplace_back(&AssetsManager::loadSingleTexture, path, false);
    }

    for(auto &thread: threads){
        thread.join();
    }

}
