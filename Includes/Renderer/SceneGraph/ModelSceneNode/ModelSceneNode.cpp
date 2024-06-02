//
// Created by wpsimon09 on 29/01/24.
//

#include "ModelSceneNode.h"

#include <utility>

ModelSceneNode::ModelSceneNode(std::string path, bool supportsAreaLight, std::shared_ptr<Material> mat, std::string name): SceneNode() {
    Assimp::Importer importer;

    this->material = std::move(mat);
    this->name = name;
    this->supportsIBL = true;
    this->supportsAreaLight = supportsAreaLight;
    const aiScene *scene = importer.ReadFile(path.c_str(),
                                             aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace | aiProcess_OptimizeGraph );

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    this->wasFound = true;
    this->directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);

}

void ModelSceneNode::processNode(aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        //this->threads.emplace_back(&ModelSceneNode::processRenderable,this, mesh, scene);
        this->processRenderable(mesh, scene);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        this->processNode(node->mChildren[i], scene);
    }
}

void ModelSceneNode::processRenderable(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertecies;
    std::vector<unsigned int> indecies;

    std::thread verteciesProcessor(ModelLoaderHelper::processVertecies, std::ref(vertecies), mesh, scene);

    std::thread indeciesProcessor(ModelLoaderHelper::processIndecies, std::ref(indecies), mesh);

    verteciesProcessor.join();
    indeciesProcessor.join();

    aiMaterial* meshMaterial = scene->mMaterials[mesh->mMaterialIndex];

    std::unique_ptr<Geometry> renderableGeometry = std::make_unique<ModelGeometry>(name.empty() ? std::string(mesh->mName.C_Str()) : name,vertecies, indecies);

    std::shared_ptr<Material> renderableMaterial;
    bool hasModelTextures;
    if(this->material == nullptr){
        renderableMaterial = this->processRenderableMaterial(meshMaterial);
        hasModelTextures = true;
    }
    else{
        renderableMaterial = this->material;
        hasModelTextures = false;
    }

    std::string renderableName = mesh->mName.C_Str() + std::to_string(this->processedRenderableCount);

    std::unique_ptr<Renderable> processedRenderable = std::make_unique<Renderable>(std::move(renderableGeometry), renderableMaterial, renderableName);

    processedRenderable->isModel = hasModelTextures;

    std::unique_ptr<SceneNode> processedNode = std::make_unique<SceneNode>(std::move(processedRenderable));

    this->processedRenderableCount++;
    this->addChild(std::move(processedNode));
}

std::unique_ptr<PBRTextured>ModelSceneNode::processRenderableMaterial(aiMaterial *meshMaterial) {
    std::unique_ptr<PBRTextured> mat = std::make_unique<PBRTextured>(this->supportsAreaLight);

    std::vector<std::shared_ptr<Texture2D>> materialTextures;
    std::lock_guard<std::mutex> lock(this->textureGuard);

    std::thread albedoProcessor(&ModelSceneNode::processMaterialPropertyMultythreaded, meshMaterial, aiTextureType_DIFFUSE);

    mat->addTexture(this->processMaterialProperty(meshMaterial, aiTextureType_DIFFUSE , "_albedoMap", 0));

    mat->addTexture(this->processMaterialProperty(meshMaterial, aiTextureType_DIFFUSE_ROUGHNESS, "_rougnessMap", 1));

    mat->addTexture(this->processMaterialProperty(meshMaterial, aiTextureType_METALNESS, "_metalnessMap", 2));

    mat->addTexture(this->processMaterialProperty(meshMaterial, aiTextureType_NORMALS, "_normalMap", 3));

    mat->addTexture(this->processMaterialProperty(meshMaterial, aiTextureType_AMBIENT_OCCLUSION, "_aoMap", 4));

    mat->addTexture(this->processMaterialProperty(meshMaterial, aiTextureType_EMISSIVE, "_emmisionMap", 5));

    mat->addTexture(this->processMaterialProperty(meshMaterial, aiTextureType_UNKNOWN, "_rougnessMetalnessMap", 6));

    mat->hasEmissionTexture = this->hasEmissionTexture;

    return std::move(mat);
}

std::unique_ptr<PBRMaterial<Texture2D>>
ModelSceneNode::processMaterialProperty(aiMaterial *material, aiTextureType type, const std::string& shaderName,const int samplerID) {
        aiString path;

        if(material->GetTexture(type, 0, &path) == AI_SUCCESS){
            if(type == aiTextureType_EMISSIVE){
                this->hasEmissionTexture = true;
            }
            for(auto &loaded_texture : this->loadedTextures ){
                if(std::strcmp(loaded_texture->getFullPath().c_str(), path.C_Str()) == 0){
                    return std::make_unique<PBRMaterial<Texture2D>>(loaded_texture, shaderName,samplerID);
                }
            }

            Texture2D loadedTexture((directory +"/"+path.C_Str()).c_str());
            this->loadedTextures.push_back(std::make_shared<Texture2D>(loadedTexture));
            return std::make_unique<PBRMaterial<Texture2D>>(loadedTexture, shaderName, samplerID);
        }

        return nullptr;
}

void ModelSceneNode::castsShadow(bool hasShadow) {
    for(auto &child: this->children){
        if(child->getRenderable() != nullptr){
            child->getRenderable()->castsShadwo = hasShadow;git
        }
    }
}

void ModelSceneNode::supportsIbl(bool supportsIBL) {
    for(auto &child: this->children){
        if(child->getRenderable() != nullptr){
            child->getRenderable()->getObjectMaterial()->supportsIBL = supportsIBL;
        }
    }
}





