//
// Created by wpsimon09 on 26/01/24.
//

#ifndef PABLO_RENDERER_MODELRENDERABLE_H
#define PABLO_RENDERER_MODELRENDERABLE_H

#include "Renderer/Renderable/Renderable.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/ai_assert.h>
#include <assimp/scene.h>
#include <vector>
//load model
//load verticies
//  - rewrote the constructor for geometry loader to accept just vao
//  - try to create the scene node structure from the model
//  - use it as option to load as scene node or as single vao
//load materials
//  - overload the constructor to accept the materials loaded from the model
//  - alternativly create setters for different materials


class ModelRenderable: public Renderable{
    public:
        explicit ModelRenderable(std::string path);
        void setMaterial(PBRTextured* material);
        std::string directory;
    private:
        std::vector<Vertex> modelVertices;
        std::vector<unsigned int> modelIndecies;
        std::vector<Texture2D> loadedTextures;
        void processNode(aiNode* node, const aiScene* scene);
        void processMesh(aiMesh* mesh, const aiScene* scene);
        void loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};


#endif //PABLO_RENDERER_MODELRENDERABLE_H
