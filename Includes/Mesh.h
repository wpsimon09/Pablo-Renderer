#pragma once
#ifndef MESH_H
#define MESH_H
#include "vector"

/*
struct Vertex
{
	glm::vec3 Postion;
	glm::vec3 Normal;
	glm::vec2 TexCoords;

	glm::vec3 Tangents;
	glm::vec3 Bitangents;
};
*/

struct _Texture
{
	unsigned int id;
	std::string path;
	std::string type;
};

class Mesh {
public:
	std::vector <Vertex> vertecies;
	std::vector <unsigned int> indecies;
	std::vector <_Texture> textures;

	Mesh(std::vector<Vertex> vertecies, std::vector<unsigned int> indecies, std::vector<_Texture> texutres);
	void Draw(Shader& shader);
	void DrawInstanced(Shader& shader);

	void setAmountOfDrawCals(unsigned int drawCalls) {
		this->drawCalls = drawCalls;
	}
private:
	unsigned int drawCalls;

	//initialize the buffers
	//--------------
	void setupMesh();
	void setupTextures(Shader &shader);
};

Mesh::Mesh(std::vector<Vertex> vertecies, std::vector<unsigned int> indecies, std::vector<_Texture> texutres)
{
	this->vertecies = vertecies;
	this->indecies = indecies;
	this->textures = texutres;

    setupMesh();
}

void Mesh::setupMesh() 
{
    size_t vec3Size = sizeof(glm::vec3);
    size_t vec2Size = sizeof(glm::vec2);

}

void Mesh::Draw(Shader& shader) {
	
	this->setupTextures(shader);

	//draw mesh
	glDrawElements(GL_TRIANGLES, indecies.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::DrawInstanced(Shader& shader)
{
	//draw mesh
	glDrawElementsInstanced(GL_TRIANGLES, indecies.size(), GL_UNSIGNED_INT, 0, this->drawCalls);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void Mesh::setupTextures(Shader &shader)
{
	
	shader.use();
	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		std::string number;
		std::string name = textures[i].type;
        //std::cout<<"GL_ACTIVE_TEXTURE"<0+i<<" with type: "<<textures[i].type <<std::endl;
		shader.setInt((name).c_str(), i);
        glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
    glActiveTexture(GL_TEXTURE0);

}

#endif // !1