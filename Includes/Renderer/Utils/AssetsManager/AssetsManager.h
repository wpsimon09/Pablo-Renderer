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

#include "Renderer/Material/Material.h"

/**
 * @brief Holds textures and in the future models used in the engine, @todo Extend to all shapes and models
 */
class AssetsManager {
public:
    static AssetsManager *getInstance();

    /**
     * @brief Retrieves multiple textures. @note this method is usin multy-threading and might liead to some problems
     * @param paths paths of the textures to load or retrieve
     * @return vector of the loaded textures
     */
    std::vector<std::shared_ptr<Texture2D>> getMultipleTextures(std::vector<std::string> paths);

    /**
     * @brief Retreives single texture on separate thread ensuring thread safety
     * @param path path of the texture to retrieve
     * @return retrieved textured
     */
    std::shared_ptr<Texture2D> getTextureOnThread(std::string path);

    /**
     * @brief Retrieves single thexture on main thread without ensuring thread safetyness
     * @param path path to the texture to retrieve
     * @return retrived textured
     */
    std::shared_ptr<Texture2D> getTexture(std::string path);

    /**
     * @brief Retrieves all loaded textues
     * @return map of all the textures loaded together with theair paths
     */
    const std::vector<std::shared_ptr<Texture2D>> getLoadedTextures();

    /**
     * @brief Loades all of the textures that are loaded in assets manager to the OpenGL
     */
    void loadTexturesToOpenGL();

    void storeMaterial(std::shared_ptr<Material> newMaterial);

    void storeTexture(std::shared_ptr<Texture2D> newTexture);

    std::vector<std::shared_ptr<Material>> getExistingMaterisl(MATERIAL materialType = ALL);

    /**
     * @brief Retrieves the material with the corresponding texture
     * @param fileName file name of the albeod texture to check against
     * @return allreayLoaded PBR Textured material;
     */
    std::shared_ptr<Material> getMaterialByAlbedoTexture(std::string fileName);

    std::shared_ptr<Material> getMaterialByAssimpIndex(unsigned int assimpIndex);

    ~AssetsManager() = default;

private:
    /***
     * @brief Path to where engine is stored this configured in cMAKE and might always give error in IDE
     */
    std::string projectPath = PABLO_PATH;

    /**
     * @brief Mutex for thread locking and te
     */
    inline static std::mutex textureLock;

    AssetsManager() = default;

    /**
     * @brief Instance for Singelton purposes
     */
    static inline AssetsManager *instance;

    /**
     * @brief Loads single texture to the assets manager and returns shared pointer to it
     * @param path path of the texture
     * @param toGL boolean flag that determines if the texture is going to be loaded to openGl or not
     * this paramater is for the purpose of multy-threading without creating additiona OpenGL contexts
     * default value is True, if false the texture Data will be copied and stored inside the texture instance.
     * It is up to the user to ensure that the texture will acctualy by loaded to OpenGL in order to be used.
     * @return shared pointer to the loaded texture instance
     */
    std::shared_ptr<Texture2D> loadSingleTexture(const char *path, bool toGL = true);

    static inline void
    loadSingleTextureOnThread(const char *path, std::vector<std::shared_ptr<Texture2D>> &tempStorage);

    std::vector<std::shared_ptr<Texture2D>> loadMultipleTextures(std::vector<const char *> texturePaths);

    std::map<std::string,  std::shared_ptr<Texture2D>> loadedTextures;

    std::map<unsigned int, std::shared_ptr<Material>> loadedMaterials;
};


#endif //PABLO_RENDERER_ASSETSMANAGER_H
