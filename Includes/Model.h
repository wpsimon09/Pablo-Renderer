#pragma once
#ifndef MODEL_H
#define MODEL_H
#include<glad/glad.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<stb_image.h>
#include<assimp/Importer.hpp>
#include<assimp/postprocess.h>
#include<assimp/ai_assert.h>
#include<assimp/scene.h>
#include "Renderer/Utils/Vertex/Vertex.h"
#include "Shader.h"
#include "Mesh.h"
#include "Renderer/Utils/VAO/VAO.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);


class Model {
	public:
		Model(const char* path, unsigned int drawCalls = 1)
		{
			loadModel(path);
			this->drawCalls = drawCalls;
		}

        VAO* parseToRenderable();

		void Draw(Shader& shader);
		void DrawInstaced(Shader& shader);
		std::vector<Mesh> meshes;
	private:
		unsigned int drawCalls;
		//model data
		std::string directory;
		std::vector<_Texture> textures_loaded;
        std::vector<Vertex> modelVerticies;
        std::vector<unsigned int> modelIndecies;

		void loadModel(std::string path);
		void processNode(aiNode* node, const aiScene* scene);
		Mesh processMesh(aiMesh* mesh, const aiScene* scene);
		std::vector<_Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

/*
* Loops through all of the meshes and draw them using their own 
* draw method
*/
void Model::Draw(Shader& shader) {
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].setAmountOfDrawCals(this->drawCalls);
		meshes[i].Draw(shader);
	}
}

VAO* Model::parseToRenderable() {
    return new VAO(this->modelVerticies, this->modelIndecies);
}

void Model::DrawInstaced(Shader& shader)
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i].setAmountOfDrawCals(this->drawCalls);
		meshes[i].DrawInstanced(shader);
	}
}


/*
* Loads model using Assimp importer class
*/
void Model::loadModel(std::string path) {
	Assimp::Importer importer;
	
	/*
	* Loads all of the file data to the sceneobject
	* 
	* @param: path - path to the object file
	* @param: postproccesing arguments - postprocessing arguments
	* 
	* aiProcess_triangles - assimp convert everything to triagles
	* aiProcess_flipUvS - assimp will flip textures accordingly
	* 
	*/
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	this->directory = path.substr(0, path.find_last_of('/'));
	processNode(scene->mRootNode, scene);
	
	std::cout << "-------------------MODEL PROCESSED--------------------------\n\n\n";
}


void Model::processNode(aiNode* node, const aiScene* scene) {
	
	// process all nodes
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		//scene has multiple nodes and node indexes mesh
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}

	//process node's schildren
	for (unsigned int  i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertecies;
	std::vector<unsigned int> indecies;
	std::vector<_Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		//proccess vertex positions
		glm::vec3 tempVertex;
		tempVertex.x = mesh->mVertices[i].x;
		tempVertex.y = mesh->mVertices[i].y;
		tempVertex.z = mesh->mVertices[i].z;
		vertex.position = tempVertex;

		if (mesh->HasNormals())
		{

			tempVertex.x = mesh->mNormals[i].x;
			tempVertex.y = mesh->mNormals[i].y;
			tempVertex.z = mesh->mNormals[i].z;
			
			vertex.normals = tempVertex;

		}
		else 
			std::cout << "ERROR::ASSIMP::PROCCESSING::NORMALS - There are no normal vectors in the model\n";
	
		//process normal vectors
		//process texture coordinates
		glm::vec2 tempTexCoords;

		if (mesh->mTextureCoords[0])
		{			
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
		}
		else {
			std::cout << "ERROR::ASSIMP::PROCCESSING::TEXTURE::COORDINATES - There are no texture coordinates to process\n";
			vertex.uv = glm::vec2(0.0f, 0.0f);
		}
        modelVerticies.push_back(vertex);
		//vertecies.push_back(vertex);
	}
	
	//process numIndecies
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		//each mesh contains n number of faces
		//each face contains n number of numIndecies
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indecies.push_back(face.mIndices[j]);
            this->modelIndecies.push_back(face.mIndices[j]);
		}
	}
	
	//process material
	if (scene->mNumMaterials > 0)
	{
		// load diffuse textures
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		
		std::vector<_Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "_albedoMap");
		//insert on the end of texture vector
		//from diffuse maps begin to diffuse map end
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		// load specular textures
		std::vector<_Texture> rougnessMap = loadMaterialTextures(material, aiTextureType_UNKNOWN, "_rougnessMap");

		textures.insert(textures.end(), rougnessMap.begin(), rougnessMap.end());

		// load normal	
		std::vector<_Texture> normalMaps = loadMaterialTextures(material, aiTextureType_NORMALS, "_normalMap");
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

        // load emmision
        std::vector<_Texture> emisionMaps = loadMaterialTextures(material, aiTextureType_EMISSIVE, "_emmisionMap");
        textures.insert(textures.end(), emisionMaps.begin(), emisionMaps.end());

	}
	else 
		std::cout << "ERROR::ASSIMP::PROCCESSING::MATERIALS - There are no materials to be proccessed\n";

	std::cout << "--------------------------------------------------------------\n";
	std::cout << "-------------------  MESH LOADING DONE  -------------------------\n";
	std::cout << "------------------- VERTECIES PROCESSED ------------------------\n";
	std::cout << "-------------------  INDECIES PROCESSED -------------------------\n";
	std::cout << "------------------- MATERIALS PROCESSED ------------------------\n";
	std::cout << "--------------------------------------------------------------\n\n\n";

    Mesh _mesh(vertecies, indecies, textures);
	return _mesh;
}

std::vector<_Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName) {
	std::vector<_Texture> textures;

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		bool skip = false;
		for (auto & j : textures_loaded)
		{
			if (std::strcmp(j.path.data(),str.C_Str()) == 0)
			{
				textures.push_back(j);
				skip = true;
				break;
			}
		}
		if (!skip)
		{ // if texture hasnt been loaded already, load it
			_Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			textures_loaded.push_back(texture); // add to loaded textures
		}
	}

	return textures;
}

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma)
{
	std::string filename = std::string(path);
	filename = directory + "/" + filename;
    std::cout<<"Loading texture at path: "<<filename<<std::endl;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << filename << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

#endif // !MODEL_H
