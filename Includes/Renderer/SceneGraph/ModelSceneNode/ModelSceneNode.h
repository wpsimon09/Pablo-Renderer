//
// Created by wpsimon09 on 29/01/24.
//

#ifndef PABLO_RENDERER_MODELSCENENODE_H
#define PABLO_RENDERER_MODELSCENENODE_H

#include "Renderer/Renderable/Renderable.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/ai_assert.h>
#include <assimp/scene.h>
#include <vector>
#include "Renderer/SceneGraph/SceneNode/SceneNode.h"

class ModelSceneNode:public SceneNode  {
public:
    explicit ModelSceneNode(Shader* shader, std::string path);
    std::string directory;
    static inline SceneNode* rootNode;
private:
    Shader *shader;
    Material *modelMaterial;
    std::vector<std::unique_ptr<Texture2D>>loadedTextures;
    void processNode(aiNode* node, const aiScene* scene);
    void processRenderable(aiMesh* mesh, const aiScene* scene);
    Material *processRenderableMaterial(aiMaterial* meshMaterial);
    std::unique_ptr<PBRMaterial<Texture2D>> processMaterialProperty(aiMaterial* material, aiTextureType type, const std::string& shaderName, const int samplerID);
};


#endif //PABLO_RENDERER_MODELSCENENODE_H
