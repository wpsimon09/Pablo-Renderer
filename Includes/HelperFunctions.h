#ifndef CLIONTEST_HELPERFUNCTIONS_H
#define CLIONTEST_HELPERFUNCTIONS_H
#include <iostream>
#include <glm/glm.hpp>
#include <Shader.h>
#include "stb_image.h"

#define COLOR_RED glm::vec3(1.0f, 0.0f, 0.0f)
#define COLOR_GREEN glm::vec3(0.0f, 1.0f, 0.0f)
#define COLOR_BLUE glm::vec3(0.0f, 0.0f, 1.0f)
#define COLOR_YELLOW glm::vec3(1.0f, 1.0f, 0.0f)
#define COLOR_MAGENTA glm::vec3(1.0f, 0.0f, 1.0f)
#define COLOR_CYAN glm::vec3(0.0f, 1.0f, 1.0f)
#define COLOR_WHITE glm::vec3(1.0f, 1.0f, 1.0f)
#define COLOR_BLACK glm::vec3(0.0f, 0.0f, 0.0f)
#define COLOR_SUN colorOf(253.0f, 251.0f, 211.0f);

glm::vec3 colorOf(float r, float g, float b) {
	glm::vec3 color;
	color.x = r / 255.0f;
	color.y = g / 255.0f;
	color.z = b / 255.0f;

	return color;
}


unsigned int loadTexture(const char *path, bool gammaCorrection)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum internalFormat;
		GLenum dataFormat;
		if (nrComponents == 1)
		{
			internalFormat = dataFormat = GL_RED;
		}
		else if (nrComponents == 3)
		{
			internalFormat = gammaCorrection ? GL_SRGB : GL_RGB;
			dataFormat = GL_RGB;
		}
		else if (nrComponents == 4)
		{
			internalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
			dataFormat = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,nrComponents == 4 ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, nrComponents == 4 ? GL_CLAMP_TO_EDGE : GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
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
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

unsigned int loadIrradianceMap(const char *path)
{
	unsigned int textureID;
	int width, height, nrComponents;

	float* data = stbi_loadf(path, &width, &height, &nrComponents, 0);
	

	if (data)
	{
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB,
			GL_FLOAT, data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		std::cout << "HDRi texture loaded! " << std::endl;
		std::cout << "Width: " << width << std::endl;
		std::cout << "Height: " << height << std::endl;
		std::cout << "Nr components: " << nrComponents << std::endl <<std::endl;

		stbi_image_free(data);
	}
	else
	{
		std::cout << "ERROR::FAILED TO LOAD IRRADIANCE MAP :: PATH: \n";
		std::cout << path << std::endl;
	}
	return textureID;
}


void useTexture(unsigned int samplerNumber, unsigned int texture)
{
	glActiveTexture(GL_TEXTURE0 + samplerNumber);
	glBindTexture(GL_TEXTURE_2D, texture);
}


void setMatrices(Shader shader ,glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	shader.use();
	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
}



float cubeVertices[] = {
	 // back face
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
             1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
            -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
            -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
            // front face
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
             1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
            -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
            -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
            // left face
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            -1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
            -1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
            // right face
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
             1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
             1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
             1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
            // bottom face
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
             1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
             1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
            -1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
            -1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
            // top face
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
             1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
             1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
             1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
            -1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
            -1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left
};

float planeVertices[] = {
        // positions                            // normals                               // texcoords
        // positions            // normals         // texcoords
        100.0f, -0.5f,  100.0f,  0.0f, 100.0f, 0.0f,  100.0f,  0.0f,
        -100.0f, -0.5f,  100.0f,  0.0f, 100.0f, 0.0f,   0.0f,  0.0f,
        -100.0f, -0.5f, -100.0f,  0.0f, 100.0f, 0.0f,   0.0f, 100.0f,

        100.0f, -0.5f,  100.0f,  0.0f, 100.0f, 0.0f,  100.0f,  0.0f,
        -100.0f, -0.5f, -100.0f,  0.0f, 100.0f, 0.0f,   0.0f, 100.0f,
        100.0f, -0.5f, -100.0f,  0.0f, 100.0f, 0.0f,  100.0f, 100.0f
};

float screeneSpaceQuadVertecies[] = {
        // positions        // texture Coords
        -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
};

float lightVertices[] = {
	// positions          // texture coords
	0.0f, 0.0f, 0.0f,	  0.0f, 0.0f,
	1.0f, 0.0f, 0.0f,	  1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,	  0.0f, 1.0f,

	1.0f, 0.0f, 0.0f,	  1.0f, 0.0f,
	1.0f, 1.0f, 0.0f,	  1.0f, 1.0f,
	0.0f, 1.0f, 0.0f,	  0.0f, 1.0f
};

float wallVertecies[] = {
        0.0f, 0.0f, 0.0f,	     0.0f, 0.0f, 1.0f,	0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,	    0.0f, 0.0f, 1.0f, 	1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,	0.0f, 0.0f, 1.0f, 	0.0f, 1.0f,

        1.0f, 0.0f, 0.0f,	0.0f, 0.0f, !.0f,	1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,	0.0f, 0.0f, !.0f,	1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,	0.0f, 0.0f, !.0f,	0.0f, 1.0f
};
float HDRframeBufferVertecies[] = {
	// positions        // texture Coords
	-1.0f,  0.2f, 0.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
	 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
};

float debugQuadVertices[] = {
        // positions                            // texture Coords
        0.30f,  0.40f, 0.0f, 0.0f, 0.0f, // bottom left
        0.30f, 1.0f, 0.0f, 0.0f, 1.0f, // top left
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // top right
        
        0.30f,  0.40f, 0.0f, 0.0f, 0.0f, // bottom left
        1.0f, 0.40f, 0.0f, 1.0f, 0.0f, // bottom right
        1.0f,  1.0f, 0.0f, 1.0f, 1.0f, // top right
};

#endif