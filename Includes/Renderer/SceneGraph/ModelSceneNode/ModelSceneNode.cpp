//
// Created by wpsimon09 on 29/01/24.
//

#include "ModelSceneNode.h"

#include <utility>

ModelSceneNode::ModelSceneNode(std::string path, bool supportsAreaLight, std::shared_ptr<Material> mat, std::string name): SceneNode() {
    Assimp::Importer importer;

    StopWatch::Start();

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
    ModelLoaderHelper::setDirectory(this->directory);

    processNode(scene->mRootNode, scene);

    StopWatch::End();

    std::cout<<"Model loaded in:"<< StopWatch::GetTimeInSec() << " sec"<< std::endl;
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

    /***
     * @brief Geometry processing
     */
    std::vector<Vertex> vertecies;
    std::vector<unsigned int> indecies;

    std::thread verteciesProcessor(ModelLoaderHelper::processVertecies, std::ref(vertecies), mesh, scene);

    std::thread indeciesProcessor(ModelLoaderHelper::processIndecies, std::ref(indecies), mesh);

    verteciesProcessor.join();
    indeciesProcessor.join();

    /***
     * @brief Material Processing
     */
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

    /***
     * @brief Assembling material and geomtry together
     */
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

    std::vector<std::thread> textureThreads;
    /***
     * @brief Create threads
     */
    for(auto &texture: materialsToLoad ){
        textureThreads.emplace_back(&ModelLoaderHelper::processMaterialTexture,meshMaterial,texture,std::ref(materialTextures));
    }

    /***
     * @brief Sync threads
     */
    for(auto &thread: textureThreads){
        thread.join();
    }

    /***
     * @brief assign names and samplers
     */
    int i = 0;
    for(auto &textureToLoad : materialTextures){
        auto newTexture = std::make_unique<PBRMaterial<Texture2D>>(textureToLoad, textureToLoad->shaderName, textureToLoad->samplerID);
        newTexture->type->passToOpenGL();
        mat->addTexture(std::move(newTexture));
        i++;
    }

    mat->hasEmissionTexture = ModelLoaderHelper::hasEmmision();

    return std::move(mat);
}


void ModelSceneNode::castsShadow(bool hasShadow) {
    for(auto &child: this->children){
        if(child->getRenderable() != nullptr){
            child->getRenderable()->castsShadwo = hasShadow;
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





