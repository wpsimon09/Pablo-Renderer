//
// Created by wpsimon09 on 29/01/24.
//

#include "ModelSceneNode.h"

ModelSceneNode::ModelSceneNode(Shader *shader, std::string path): SceneNode() {
    this->shader = shader;
    Assimp::Importer importer;

    const aiScene *scene = importer.ReadFile(path.c_str(),
                                             aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace );

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

    aiMaterial* meshMaterial = scene->mMaterials[mesh->mMaterialIndex];

    Geometry* renderableGeometry = new ModelGeometry(std::string(mesh->mName.C_Str()),vertecies, indecies);
    Material* renderableMaterial = this->processRenderableMaterial(meshMaterial);
    Renderable* processedRenderable = new Renderable(renderableGeometry, renderableMaterial, mesh->mName.C_Str());

    this->addChild(new SceneNode(processedRenderable));
}

Material *ModelSceneNode::processRenderableMaterial(aiMaterial *meshMaterial) {
    PBRMaterial<Texture2D>* baseColor = this->processMaterialProperty(meshMaterial, aiTextureType_DIFFUSE ,"_albedoMap");
    if(baseColor != nullptr)
        baseColor->type.setSamplerID(0);

    PBRMaterial<Texture2D>* rougness = this->processMaterialProperty(meshMaterial, aiTextureType_DIFFUSE_ROUGHNESS,"_rougnessMap");
    if(rougness != nullptr)
        rougness->type.setSamplerID(1);

    PBRMaterial<Texture2D>* metalness = this->processMaterialProperty(meshMaterial, aiTextureType_METALNESS,"_metalnessMap");
    if(metalness != nullptr)
        metalness->type.setSamplerID(2);

    PBRMaterial<Texture2D>* normalMap = this->processMaterialProperty(meshMaterial, aiTextureType_NORMALS,"_normalMap");
    if(normalMap!= nullptr)
        normalMap->type.setSamplerID(3);

    PBRMaterial<Texture2D>* ao = this->processMaterialProperty(meshMaterial, aiTextureType_AMBIENT_OCCLUSION,"_aoMap");
    if(ao != nullptr)
        ao->type.setSamplerID(4);

    PBRMaterial<Texture2D>* emmisionMap = this->processMaterialProperty(meshMaterial, aiTextureType_EMISSIVE,"_emmisionMap");
    if(emmisionMap != nullptr)
        emmisionMap->type.setSamplerID(5);

    PBRMaterial<Texture2D>* rougnessMetalnessMap = this->processMaterialProperty(meshMaterial, aiTextureType_UNKNOWN,"_rougnessMetalnessMap");
    if(rougnessMetalnessMap != nullptr)
        rougnessMetalnessMap->type.setSamplerID(6);

    return new PBRTextured(shader, baseColor, normalMap, emmisionMap, rougnessMetalnessMap, rougness, metalness, ao);
}

PBRMaterial<Texture2D> *
ModelSceneNode::processMaterialProperty(aiMaterial *material, aiTextureType type, const std::string& shaderName) {
        aiString path;

        if(material->GetTexture(type, 0, &path) == AI_SUCCESS){
            for(auto &loaded_texture : this->loadedTextures ){
                if(std::strcmp(loaded_texture.getFullPath().c_str(), path.C_Str()) == 0){
                    std::cout<<"texutre has allready been loaded"<<std::endl;
                    std::cout<<loaded_texture.getFullPath()<<std::endl;
                    return new PBRMaterial<Texture2D>(loaded_texture, shaderName);
                }
            }

            Texture2D loadedTexture((directory +"/"+path.C_Str()).c_str());
            this->loadedTextures.push_back(loadedTexture);
            std::cout<<"texutre has not been allready been loaded"<<std::endl;
            std::cout<<loadedTexture.getFullPath()<<std::endl;
            return new PBRMaterial<Texture2D>(loadedTexture, shaderName);
        }
        return nullptr;
}


