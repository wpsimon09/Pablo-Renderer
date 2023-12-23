#pragma once
#include <iostream>
#include <glm/glm.hpp>
#include "Shader.h"

struct DirLight {
	glm::vec3 direction;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct PointLight {
	float constant;
	float linear;
	float quadratic;

	glm::vec3 position;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

struct SpotLight {
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	bool isOn;

	glm::vec3 position;
	glm::vec3 direciton;
	
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class Light  
{
	public:
		Light(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
		Light(float constant, float linear, float quadratic, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
		Light(float cutOff, float outerCutOFF,float constant, float linear, float quadratic, bool isOn, glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

		void setLight(Shader &shader);

		std::string getType();
	private:
		PointLight _pointLight;
		DirLight _dirLight;
		SpotLight _spotLight;
		std::string lightType;
};


Light::Light(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
	this->_dirLight.direction = direction;
	this->_dirLight.ambient = ambient;
	this->_dirLight.diffuse = diffuse;
	this->_dirLight.specular = specular;

	this->lightType = "dir";
}

Light::Light(float cutOff, float outerCutOFF, float constant, float linear, float quadratic,bool isOn, glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	this->_spotLight.constant = constant;
	this->_spotLight.linear = linear;
	this->_spotLight.quadratic = quadratic;

	this->_spotLight.isOn = isOn;
	this->_spotLight.position = position;
	
	this->_spotLight.ambient = ambient;
	this->_spotLight.diffuse = diffuse;
	this->_spotLight.specular = specular;

	this->lightType = "spot";
}

Light::Light(float constant, float linear, float quadratic, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) {
	this->_pointLight.constant = constant;
	this->_pointLight.linear = linear;
	this->_pointLight.quadratic = quadratic;
	this->_pointLight.position = position;
	this->_pointLight.ambient = ambient;
	this->_pointLight.diffuse = diffuse;
	this->_pointLight.specular = specular;

	this->lightType = "point";
}

void Light::setLight(Shader& shader) {
	shader.use();
	shader.setFloat("material.shininess", 32);
	if (this->lightType == "dir")
	{
		shader.setVec3("dirLight.direction", this->_dirLight.direction);
		shader.setVec3("dirLight.ambient", this->_dirLight.ambient);
		shader.setVec3("dirLight.diffuse", this->_dirLight.diffuse);
		shader.setVec3("dirLight.specular", this->_dirLight.specular);
	}

	if(this->lightType == "point")
	{
		shader.setFloat("pointLights.constant", this->_pointLight.constant);
		shader.setFloat("pointLights.linear", this->_pointLight.linear);
		shader.setFloat("pointLights.quadratic", this->_pointLight.quadratic);

		shader.setVec3("pointLights.position", this->_pointLight.position);
		
		shader.setVec3("pointLights.ambient", this->_pointLight.ambient);
		shader.setVec3("pointLights.diffuse", this->_pointLight.diffuse);
		shader.setVec3("pointLights.specular", this->_pointLight.specular);
	}

	if (this->lightType == "spot")
	{
		shader.setFloat("spotLight.constant", this->_spotLight.constant);
		shader.setFloat("spotLight.linear", this->_spotLight.linear);
		shader.setFloat("spotLight.quadratic", this->_spotLight.quadratic);
		
		shader.setBool("spotLight.isOn", this->_spotLight.isOn);
		shader.setVec3("spotLight.position", this->_spotLight.position);
		
		shader.setVec3("spotLight.ambient", this->_spotLight.ambient);
		shader.setVec3("spotLight.diffuse", this->_spotLight.diffuse);
		shader.setVec3("spotLight.specular", this->_spotLight.specular);
	}
}


std::string Light::getType() {
	std::cout << this->lightType;
	return this->lightType;
}


