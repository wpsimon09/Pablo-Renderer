//
// Created by wpsimon09 on 05/06/24.
//

#ifndef PABLO_RENDERER_ASSETSMANAGER_H
#define PABLO_RENDERER_ASSETSMANAGER_H

#include "map"
#include "memory"
#include "vector"
#include "mutex"
#include "thread"
#include "Renderer/Utils/Texture/Texture2D/Texture2D.h"
#include <iostream>

class AssetsManager {
public:
    static AssetsManager *getInstance();

    std::vector<std::shared_ptr<Texture2D>> getMultipleTextures(std::vector<const char *> paths);

    std::shared_ptr<Texture2D> getTexture(const char *path);

    ~AssetsManager() = default;

private:
    inline static std::mutex textureLock;

    AssetsManager() = default;

    static inline AssetsManager *instance;

    std::shared_ptr<Texture2D> loadSingleTexture(const char *path, bool toGL = true);

    static inline void
    loadSingleTextureOnThread(const char *path, std::vector<std::shared_ptr<Texture2D>> &tempStorage);

    std::vector<std::shared_ptr<Texture2D>> loadMultipleTextures(std::vector<const char *> texturePaths);

    std::map<const char *, std::shared_ptr<Texture2D>> loadedTextures;
};


#endif //PABLO_RENDERER_ASSETSMANAGER_H
