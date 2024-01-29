//
// Created by wpsimon09 on 29/01/24.
//

#include "ModelSceneNode.h"

ModelSceneNode::ModelSceneNode(Shader *shader, std::string path) {
    this->shader = shader;
    ModelSceneNode::rootNode = new SceneNode();

    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(path.c_str(),
                                             aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    this->directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);

}

void ModelSceneNode::processNode(aiNode *node, const aiScene *scene) {
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        this->processRenderable(mesh, scene);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        this->processNode(node->mChildren[i], scene);
    }
}

void ModelSceneNode::processRenderable(aiMesh *mesh, const aiScene *scene) {
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
        vertecies.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indecies.push_back(face.mIndices[j]);
        }
    }
    Geometry* renderableGeometry = new ModelGeometry(std::string(mesh->mName.C_Str()),vertecies, indecies);
    Material* renderableMaterial = loadMaterialTextures(scene);
    Renderable* processedRenderale = new Renderable(renderableGeometry, renderableMaterial, mesh->mName.C_Str());

    ModelSceneNode::rootNode->addChild(new SceneNode(processedRenderale));
}

Material *ModelSceneNode::loadMaterialTextures(const aiScene *scene) {
    PBRMaterial<Texture2D>* baseColor = nullptr;
    PBRMaterial<Texture2D>* rougness = nullptr;
    PBRMaterial<Texture2D>* metalness = nullptr;
    PBRMaterial<Texture2D>* normalMap = nullptr;
    PBRMaterial<Texture2D>* ao = nullptr;
    PBRMaterial<Texture2D>* emmisionMap = nullptr;
    PBRMaterial<Texture2D>* rougnessMetalnessMap = nullptr;


    for (unsigned int i = 0; i < scene->mNumMaterials; ++i) {
        aiMaterial* material = scene->mMaterials[i];

        aiString texturePath;
        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
            std::string path = directory + "/" + texturePath.C_Str();
            Texture2D texture( path.c_str(), true);
            texture.setSamplerID(0);
            baseColor = new PBRMaterial<Texture2D>(texture, "_albedoMap");

            std::cout<<path<<std::endl;
        }
        if (material->GetTexture(aiTextureType_DIFFUSE_ROUGHNESS, 0, &texturePath) == AI_SUCCESS) {
            std::string path = directory + "/" + texturePath.C_Str();
            Texture2D texture(path.c_str(), true);
            texture.setSamplerID(1);
            rougness = new PBRMaterial<Texture2D>(texture, "_rougnessMap");
        }
        if (material->GetTexture(aiTextureType_METALNESS, 0, &texturePath) == AI_SUCCESS) {
            std::string path = directory + "/" + texturePath.C_Str();
            Texture2D texture( path.c_str(), true);
            texture.setSamplerID(2);
            metalness = new PBRMaterial<Texture2D>(texture, "_metalnessMap");
        }
        if (material->GetTexture(aiTextureType_NORMALS, 0, &texturePath) == AI_SUCCESS) {
            std::string path = directory + "/" + texturePath.C_Str();
            Texture2D texture( path.c_str(), true);
            texture.setSamplerID(3);
            normalMap = new PBRMaterial<Texture2D>(texture, "_normalMap");

            std::cout<<path<<std::endl;
        }
        if (material->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &texturePath) == AI_SUCCESS) {
            std::string path = directory + "/" + texturePath.C_Str();
            Texture2D texture( path.c_str(), true);
            texture.setSamplerID(4);
            ao = new PBRMaterial<Texture2D>(texture, "_aoMap");
        }
        if (material->GetTexture(aiTextureType_EMISSIVE, 0, &texturePath) == AI_SUCCESS) {
            std::string path = directory + "/" + texturePath.C_Str();
            Texture2D texture( path.c_str(), true);
            texture.setSamplerID(5);
            emmisionMap = new PBRMaterial<Texture2D>(texture, "_emmisionMap");

            std::cout<<path<<std::endl;
        }
        if (material->GetTexture(aiTextureType_UNKNOWN, 0, &texturePath) == AI_SUCCESS) {
            std::string path = directory + "/" + texturePath.C_Str();
            Texture2D texture( path.c_str(), true);
            texture.setSamplerID(6);
            rougnessMetalnessMap = new PBRMaterial<Texture2D>(texture, "_rougnessMetalnessMap");

            std::cout<<path<<std::endl;
        }
    }

    return new PBRTextured(shader, baseColor, normalMap, emmisionMap, rougnessMetalnessMap, rougness, metalness, ao);

}
