//
// Created by wpsimon09 on 12/05/24.
//

#ifndef PABLO_RENDERER_MODELLOADERHELPER_H
#define PABLO_RENDERER_MODELLOADERHELPER_H

#include "Renderer/Utils/Vertex/Vertex.h"
#include "Renderer/Utils/Texture/Texture2D/Texture2D.h"
#include "assimp/mesh.h"
#include "assimp/scene.h"
#include "vector"
#include "memory"
#include "mutex"

class ModelLoaderHelper {
private:
    inline static std::mutex textureLock;
    inline static std::vector<std::shared_ptr<Texture2D>> loadedTextures;
    inline static bool hasEmmisionTexture = false;
public:
    static void processVertecies( std::vector<Vertex> &vertecies,aiMesh* mesh, const aiScene* scene );

    static void processIndecies(std::vector<unsigned int>&indecies, aiMesh*mesh);

    static std::shared_ptr<Texture2D> processMaterialTexture(aiMaterial *material, aiTextureType type);

};


#endif //PABLO_RENDERER_MODELLOADERHELPER_H
