#ifndef CUBE_H
#define CUBE_H
#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class Cube
{
public:
	Cube();
	void dispaly(glm::mat4& model, glm::vec3 position);
	void dispaly(glm::mat4& model);
	glm::vec3 position;
	bool isDisplayed;

private:

};

Cube::Cube()
{
	isDisplayed = false;
}

void Cube::dispaly(glm::mat4& model, glm::vec3 position) {
	model = glm::translate(model, position);
	this->isDisplayed = true;
	this->position = position;
}

void Cube::dispaly(glm::mat4& model) {
	model = glm::translate(model, this->position);
}

#endif // !CUBE_H
