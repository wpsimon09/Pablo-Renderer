#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include <HelperFunctions.h>
#include <vector>

enum TextureType
{
	ALBEDO = 3,
	METALLIC = 4,
	NORMAL = 5,
	ROUGHNESS = 6,
	AO = 7
};

struct PBRTexture
{
	TextureType type;
	std::string path;

	PBRTexture(std::string path, TextureType textureType)
	{
		this->path = path;
		this->type = textureType;
	}
};

class PBRTextures
{
public:
	unsigned int albedo;
	unsigned int metallic;
	unsigned int roughness;
	unsigned int ao;
	unsigned int normal;

	PBRTextures(std::vector<PBRTexture> textures, Shader shader)
	{
		this->processTextures(textures);

		this->passToShader(shader);
	}

	PBRTextures(std::string dirPath, Shader shader)
	{
		std::vector<PBRTexture> loadedTextures = this->loadTextures(dirPath);
		this->processTextures(loadedTextures);
		this->passToShader(shader);
	}

	void useTextures()
	{
		useTexture(ALBEDO, this->albedo);
		useTexture(METALLIC, this->metallic);
		useTexture(NORMAL, this->normal);
		useTexture(ROUGHNESS, this->roughness);
		useTexture(AO, this->ao);
	}

private:
	void passToShader(Shader shader)
	{
		shader.use();
		shader.setInt("_albedoMap", ALBEDO);
		shader.setInt("_metallnesMap", METALLIC);
		shader.setInt("_normalMap", NORMAL);
		shader.setInt("_roughnessMap", ROUGHNESS);
		shader.setInt("_aoMap", AO);

	}

	void processTextures(std::vector<PBRTexture> textures)
	{
		for (int i = 0; i < textures.size(); i++)
		{
			switch (textures[i].type)
			{
			case ALBEDO: {
				this->albedo = loadTexture(textures[i].path.c_str(), true);
				break;
			}
			case METALLIC: {
				this->metallic = loadTexture(textures[i].path.c_str());
				break;
			}
			case ROUGHNESS:{
				this->roughness = loadTexture(textures[i].path.c_str());
				break;
			}
			case NORMAL:{
				this->normal = loadTexture(textures[i].path.c_str());
				break;
			}
			case AO:{
				this->ao = loadTexture(textures[i].path.c_str());
				break;
			}
			default:
				break;
			}
		}
	}

	std::vector<PBRTexture> loadTextures(std::string dirPath)
	{
		std::vector<PBRTexture> pbrTextures;
		PBRTexture albedo( dirPath + "/albedo.png", ALBEDO);
		pbrTextures.push_back(albedo);

		PBRTexture metallic(dirPath + "/metallic.png", METALLIC);
		pbrTextures.push_back(metallic);

		PBRTexture normal(dirPath + "/normal.png", NORMAL);
		pbrTextures.push_back(normal);

		PBRTexture roughness(dirPath + "/roughness.png", ROUGHNESS);
		pbrTextures.push_back(roughness);

		PBRTexture ao(dirPath + "/ao.png", AO);
		pbrTextures.push_back(ao);

		return pbrTextures;
	}

};