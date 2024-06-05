//
// Created by wpsimon09 on 05/06/24.
//

#ifndef PABLO_RENDERER_ASSETSMANAGER_H
#define PABLO_RENDERER_ASSETSMANAGER_H

#include "map"
#include "memory"
#include "vector"
#include "thread"
#include "Renderer/Utils/Texture/Texture2D/Texture2D.h"
#include <iostream>

class AssetsManager {
public:
    static inline AssetsManager* getInstance();

    std::vector<std::reference_wrapper<Texture2D>> getMultipleTextures(std::vector<int> indexes);

    std::reference_wrapper<Texture2D> getTexture(int index);

    void loadSingleTexture(const char *path, bool toGL = true);

    void loadMultipleTexutres(std::vector<const char*> texturePaths);

    ~AssetsManager();
private:
    int texturesCount = 0;

    static inline AssetsManager* instance = nullptr;

    std::map<int, std::unique_ptr<Texture2D>> loadedTextures;
};


#endif //PABLO_RENDERER_ASSETSMANAGER_H
