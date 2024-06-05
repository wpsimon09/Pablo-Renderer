//
// Created by wpsimon09 on 05/06/24.
//

#ifndef PABLO_RENDERER_ASSETSMANAGER_H
#define PABLO_RENDERER_ASSETSMANAGER_H

#include "map"
#include "memory"
#include "vector"
#include "Renderer/Utils/Texture/Texture2D/Texture2D.h"

class AssetsManager {
public:
    static inline AssetsManager* getInstance();

    void loadSingleTexture(const char *path);

    void loadMultipleTexutres(std::vector<const char*> texturePaths);

    ~AssetsManager();
private:
    static inline AssetsManager* instance;

    std::map<int, std::unique_ptr<Texture2D>> loadedTextures;
};


#endif //PABLO_RENDERER_ASSETSMANAGER_H
