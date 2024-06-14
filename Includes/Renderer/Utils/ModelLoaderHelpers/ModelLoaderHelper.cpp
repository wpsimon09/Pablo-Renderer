//
// Created by wpsimon09 on 12/05/24.
//

#include "ModelLoaderHelper.h"

#include <utility>

void ModelLoaderHelper::processVertecies(std::vector<Vertex> &vertecies, aiMesh *mesh, const aiScene *scene) {
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;
        //proccess vertex positions
        glm::vec3 tempVertex;
        tempVertex.x = mesh->mVertices[i].x;
        tempVertex.y = mesh->mVertices[i].y;
        tempVertex.z = mesh->mVertices[i].z;
        vertex.position = tempVertex;

        if (mesh->HasNormals()) {

            //process texture coordinates
            tempVertex.x = mesh->mNormals[i].x;
            tempVertex.y = mesh->mNormals[i].y;
            tempVertex.z = mesh->mNormals[i].z;

            vertex.normals = tempVertex;

        }

        //process normal vectors
        glm::vec2 tempTexCoords;

        if (mesh->mTextureCoords[0]) {
            //asimp allows for 8 different texture coorinates per verex
            //but we are only interted in the first one
            tempTexCoords.x = mesh->mTextureCoords[0][i].x;
            tempTexCoords.y = mesh->mTextureCoords[0][i].y;
            vertex.uv = tempTexCoords;

            glm::vec3 tempTangent, tempBitanget;
            if(mesh->mTangents){
                tempTangent.x = mesh->mTangents[i].x;
                tempTangent.y = mesh->mTangents[i].y;
                tempTangent.z = mesh->mTangents[i].z;
            }

            vertex.tangent = tempTangent;

            if(mesh->mBitangents){
                tempBitanget.x = mesh->mBitangents[i].x;
                tempBitanget.y = mesh->mBitangents[i].y;
                tempBitanget.z = mesh->mBitangents[i].z;
            }
            vertex.bitangent = tempBitanget;
        } else
            vertex.uv = glm::vec2(0.0f, 0.0f);
        vertecies.push_back(vertex);
    }

}

void ModelLoaderHelper::processIndecies(std::vector<unsigned int> &indecies, aiMesh *mesh) {
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indecies.push_back(face.mIndices[j]);
        }
    }
}

void ModelLoaderHelper::processMaterialTexture(aiMaterial *material, MaterialToProcess materialToLoad,
                                               std::vector<PBRMaterial<std::shared_ptr<Texture2D>>> &renderableMaterialTextures) {
    aiString path;

    if(material->GetTexture(materialToLoad.textureType, 0, &path) == AI_SUCCESS){
        if(materialToLoad.textureType == aiTextureType_EMISSIVE){
            ModelLoaderHelper::hasEmmisionTexture = true;
        }
        /*
        for(auto &loaded_texture : ModelLoaderHelper::loadedTextures ){
            if(std::strcmp(loaded_texture->getRelativePath().c_str(), path.C_Str()) == 0){
                renderableMaterialTextures.push_back(loaded_texture);
                return;
            }
        }

        auto newTexture = std::make_shared<Texture2D>((directory +"/"+path.C_Str()).c_str(), true, false);
        newTexture->setRelativePath( path.C_Str());
        newTexture->shaderName = materialToLoad.shaderName;
        newTexture->samplerID = materialToLoad.samplerNumber;
        {
            std::lock_guard<std::mutex> lock(ModelLoaderHelper::textureLock);
            ModelLoaderHelper::loadedTextures.push_back(std::move(newTexture));
            renderableMaterialTextures.push_back(loadedTextures.back());
        }*/
        std::shared_ptr<Texture2D> newTexture = assetsManagerInstance->getTextureOnThread((directory +"/"+path.C_Str()).c_str());
        auto newMaterial = PBRMaterial<std::shared_ptr<Texture2D>>(newTexture, materialToLoad.shaderName, materialToLoad.samplerNumber);
        renderableMaterialTextures.push_back(newMaterial);
    }

    else
        return;
}


