#pragma once
#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <vector>
#include <string>
#include "Shader.h"

struct Vertex
{
	glm::vec3 Postion;
	glm::vec3 Normal;
	glm::vec2 TexCoords;

	glm::vec3 Tangents;
	glm::vec3 Bitangents;
};

struct Texture
{
	unsigned int id;
	std::string path;
	std::string type;
};

class Mesh {
public:
	std::vector <Vertex> vertecies;
	std::vector <unsigned int> indecies;
	std::vector <Texture> textures;

	Mesh(std::vector<Vertex> vertecies, std::vector<unsigned int> indecies, std::vector<Texture> texutres);
	void Draw(Shader& shader);
	void DrawInstanced(Shader& shader);
	unsigned int VAO;

	void setAmountOfDrawCals(unsigned int drawCalls) {
		this->drawCalls = drawCalls;
	}
private:
	unsigned int  VBO, EBO, drawCalls;

	//initialize the buffers
	//--------------
	void setupMesh();
	void setupTextures(Shader &shader);
};

Mesh::Mesh(std::vector<Vertex> vertecies, std::vector<unsigned int> indecies, std::vector<Texture> texutres)
{
	this->vertecies = vertecies;
	this->indecies = indecies;
	this->textures = texutres;

	setupMesh();
}

void Mesh::setupMesh() 
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertecies.size() * sizeof(Vertex), &vertecies[0], GL_STATIC_DRAW);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indecies.size() * sizeof(unsigned int), &indecies[0], GL_STATIC_DRAW);


	//vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//noramls
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, Normal));

	//textures
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	//tangents
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangents));

	//bytangents
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangents));
}

void Mesh::Draw(Shader& shader) {
	
	this->setupTextures(shader);

	//draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indecies.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void Mesh::DrawInstanced(Shader& shader)
{
	this->setupTextures(shader);

	//draw mesh
	glBindVertexArray(VAO);
	glDrawElementsInstanced(GL_TRIANGLES, indecies.size(), GL_UNSIGNED_INT, 0, this->drawCalls);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupTextures(Shader &shader)
{
	unsigned int diffuseNr = 0;
	unsigned int specularNr = 0;
	unsigned int normalNr = 0;
	
	shader.use();
	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string name = textures[i].type;
		if (name == "texture_diffuse")
		{
			number = std::to_string(diffuseNr++);
		}
		else if (name == "texture_specular")
		{
			number = std::to_string(specularNr++);
		}
		else if (name == "texture_normal")
		{
			number = std::to_string(normalNr++);
		}

		shader.setInt((name + number).c_str(), i);
		//std::cout << "TEXTURE::LOADED::ASS:\n";
		//std::cout << (name + number).c_str();
		//std::cout << "\n";
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
}

#endif // !1