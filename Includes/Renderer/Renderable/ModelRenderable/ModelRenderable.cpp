//
// Created by wpsimon09 on 26/01/24.
//

#include "ModelRenderable.h"

ModelRenderable::ModelRenderable(std::string path) : Renderable() {

    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(path.c_str(),
                                             aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    this->directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
    this->objectGeometry = new ModelGeometry("model", modelVertices,modelIndecies);

}

void ModelRenderable::processNode(aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        this->processMesh(mesh, scene);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        this->processNode(node->mChildren[i], scene);
    }

}

void ModelRenderable::processMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<Vertex> vertecies;
    std::vector<unsigned int> indecies;

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

            tempTangent.x = mesh->mTangents[i].x;
            tempTangent.y = mesh->mTangents[i].y;
            tempTangent.z = mesh->mTangents[i].z;

            vertex.tangent = tempTangent;

            tempBitanget.x = mesh->mBitangents[i].x;
            tempBitanget.y = mesh->mBitangents[i].y;
            tempBitanget.z = mesh->mBitangents[i].z;

            vertex.bitangent = tempBitanget;
        } else
            vertex.uv = glm::vec2(0.0f, 0.0f);
        this->modelVertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indecies.push_back(face.mIndices[j]);
            this->modelIndecies.push_back(face.mIndices[j]);
        }
    }
}

    void ModelRenderable::loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName) {

    }

void ModelRenderable::setMaterial(PBRTextured* material) {
    this->objectMaterial = material;
}
