#pragma once
#include <iostream>
#include "Shader.h"
#include "HelperFunctions.h"
#include <glm/glm.hpp>

/// <summary>
/// Creates vertex array obect
/// VAOs are created under assumption that vertex atribute positions are like follows:
/// 0 - positions
/// 1 - normal vectors
/// 2 - texture coordinates
/// </summary>
/// <param name="vertecies">array of vertecies (positions, normals, texture coordinates</param>
/// <param name="numberOfComponents">number of components we are passing to the vertex shader</param>
/// <param name="hasNormals">true if triangle(s) have normal vector</param>
/// <param name="hasTexCoords">true if triangle(s) have texture coordinates</param>
/// <returns>Created vertex array object</returns>
unsigned int createVAO(float vertecies[], float numberOfComponents, bool hasNormals = true, bool hasTexCoords = true)
{
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfComponents , vertecies, GL_STATIC_DRAW);
	
	std::cout << "Sizeof vertecies:" << sizeof(float) * numberOfComponents << "bytes" << std::endl;

	if (hasNormals && hasTexCoords)
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

		std::cout << "Created object has 3 vertex atributes" << std::endl;
		std::cout << "0 - positions (vec3)" << std::endl;
		std::cout << "1 - normal vectors (vec3)" << std::endl;
		std::cout << "2 - texture coordinates (vec2)" << std::endl;
	}
	if (hasNormals && !hasTexCoords)
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);					
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

		std::cout << "Created object has 2 vertex atributes" << std::endl;
		std::cout << "0 - positions (vec3)" << std::endl;
		std::cout << "1 - normal vectors (vec3)" << std::endl;
	}
	if (!hasNormals && hasTexCoords)
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		
		std::cout << "Created object has 2 vertex atributes" << std::endl;
		std::cout << "0 - positions (vec3)" << std::endl;
		std::cout << "2 - texture coordinates (vec2)" << std::endl;
	}
	if (!hasNormals && !hasTexCoords)
	{
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		
		std::cout << "Created object has 1 vertex atribute" << std::endl;
		std::cout << "0 - positions (vec3)" << std::endl;
	}

	std::cout << std::endl;
	glBindVertexArray(0);

	return VAO;
}

/// <summary>
/// Creates VAO that containts position vectors, texture coordinates, normal, bitangent and tangent vectors
/// </summary>
/// <param name="data">Array of the data that containts all of the relevant information</param>
/// <param name="numberOfComponents">number of component in the given array</param>
/// <returns>vertex array object with all of the relevant information</returns>
unsigned int createVAOForTangentSpace(float data[], float numberOfComponents)
{
	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numberOfComponents, data, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(float), (void*)(11 * sizeof(float)));

	std::cout << "Created object has 3 vertex atributes" << std::endl;
	std::cout << "0 - positions (vec3)" << std::endl;
	std::cout << "1 - normal vectors (vec3)" << std::endl;
	std::cout << "2 - texture coordinates (vec2)" << std::endl;
	std::cout << "3 - tangent vector (vec3)" << std::endl;
	std::cout << "4 - bitangent vector (vec3)" << std::endl;
	return VAO;
}


/// <summary>
/// Creates VAO and EBO for sphere
/// </summary>
/// <returns>Vertex array object of sphere </returns>
unsigned int createSphereVAO(unsigned int &indexNum)
{
	unsigned int sphereVAO;
	unsigned int indexCount;
	glGenVertexArrays(1, &sphereVAO);

	unsigned int vbo, ebo;
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	std::vector<glm::vec3> positions;
	std::vector<glm::vec2> uv;
	std::vector<glm::vec3> normals;
	std::vector<unsigned int> indices;

	const unsigned int X_SEGMENTS = 64;
	const unsigned int Y_SEGMENTS = 64;
	const float PI = 3.14159265359f;
	for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
	{
		for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
		{
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

			positions.push_back(glm::vec3(xPos, yPos, zPos));
			uv.push_back(glm::vec2(xSegment, ySegment));
			normals.push_back(glm::vec3(xPos, yPos, zPos));
		}
	}

	bool oddRow = false;
	for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
	{
		if (!oddRow) // even rows: y == 0, y == 2; and so on
		{
			for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
			{
				indices.push_back(y * (X_SEGMENTS + 1) + x);
				indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
			}
		}
		else
		{
			for (int x = X_SEGMENTS; x >= 0; --x)
			{
				indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
				indices.push_back(y * (X_SEGMENTS + 1) + x);
			}
		}
		oddRow = !oddRow;
	}
	indexCount = static_cast<unsigned int>(indices.size());

	std::vector<float> data;
	for (unsigned int i = 0; i < positions.size(); ++i)
	{
		data.push_back(positions[i].x);
		data.push_back(positions[i].y);
		data.push_back(positions[i].z);
		if (normals.size() > 0)
		{
			data.push_back(normals[i].x);
			data.push_back(normals[i].y);
			data.push_back(normals[i].z);
		}
		if (uv.size() > 0)
		{
			data.push_back(uv[i].x);
			data.push_back(uv[i].y);
		}
	}
	glBindVertexArray(sphereVAO);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	unsigned int stride = (3 + 2 + 3) * sizeof(float);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));

	indexNum = indexCount;
	return sphereVAO;
}

/// <summary>
/// Creates VAO for sphere that will be rendered instaced in a grid
/// </summary>
/// <param name="rows">Number of rows in the grid</param>
/// <param name="columns">Number of colums in the grid</param>
/// <param name="instanceCount">Number of instaces</param>
/// <param name="indexCount">Index count for rendering with EBO</param>
/// <returns>Created VAO instance of the sphere</returns>
unsigned int createInstancedSphereVAO(unsigned int rows, unsigned int columns, unsigned int& instanceCount, unsigned int& indexCount)
{
	unsigned int sphereVAO = createSphereVAO(indexCount);
	glBindVertexArray(sphereVAO);
	//----------------
	// INSTANCED MODEL
	//----------------
	float currentHeight = 1.0f;

	instanceCount = rows * columns;

	std::vector<glm::mat4>modelMatrices;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(j + 1.5, currentHeight, 0.0));
			model = glm::scale(model, glm::vec3(0.4f));
			modelMatrices.push_back(model);
		}

		currentHeight = i;
	}

	unsigned int instanceBuffer;
	glGenBuffers(1, &instanceBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);
	glBufferData(GL_ARRAY_BUFFER, (rows * columns) * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);

	std::size_t v4s = sizeof(glm::vec4);

	// 1st colum of the matrix
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * v4s, (void*)0);

	//2 nd colum of the matrix
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * v4s, (void*)(1 * v4s));

	//3 rd colum of the matrix
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, 4 * v4s, (void*)(2 * v4s));

	//4 th colum of the matrix
	glEnableVertexAttribArray(8);
	glVertexAttribPointer(8, 4, GL_FLOAT, GL_FALSE, 4 * v4s, (void*)(3 * v4s));

	//update atribute arrays, 3, 4, 5, 6 each instace 
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);
	glVertexAttribDivisor(7, 1);
	glVertexAttribDivisor(8, 1);
	glBindVertexArray(0);

	return sphereVAO;
}