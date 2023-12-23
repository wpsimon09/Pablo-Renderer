#pragma once
#include <iostream>
#include "Shader.h"
#include "HelperFunctions.h"
#include <glm/glm.hpp>

/// <summary>
/// Draws the cube on the screen
/// </summary>
/// <param name="shader">Shader program that will be use when drawing the cube</param>
/// <param name="model">Model matrix that will be used NOTE: name of uniform must be "model"</param>
/// <param name="view">View matrix that will be used NOTE: name of uniform must be "view"</param>
/// <param name="projection">Projection matrix that will be used NOTE: name of uniform must be "projection"</param>
/// <param name="VAO">VAO that holds data for rendering</param>
/// <param name=""></param>
void DrawCube(Shader shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection, unsigned int VAO)
{
	shader.use();
	glBindVertexArray(VAO);

	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
}

/// <summary>
/// Renders the object to be used as a shadow map
/// </summary>
/// <param name="shader">Shader to use when drawing cube map</param>
/// <param name="model">Where is object in the world space located</param>
/// <param name="lightSpaceMatrix">Matrix that transforms coordinates to the perspective of light (projections * view)</param>
/// <param name="VAO">Vertex array object to be used</param>
void DrawShadowMapCube(Shader shader, glm::mat4 model, unsigned int VAO) 
{
	shader.use();
	glBindVertexArray(VAO);

	shader.setMat4("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindVertexArray(0);
}

/// <summary>
/// Draws plane on the scene
/// </summary>
/// <param name="shader">Shader program that will be use when drawing the cube</param>
/// <param name="model">Model matrix that will be used NOTE: name of uniform must be "model"</param>
/// <param name="view">View matrix that will be used NOTE: name of uniform must be "view"</param>
/// <param name="projection">Projection matrix that will be used NOTE: name of uniform must be "projection"</param>
/// <param name="VAO">VAO that holds data for rendering</param>
/// <param name="texture">actual texture image to use</param>
/// <param name="textureSamplerNumber">texture image sampler number</param>
/// <param name=""></param>
void DrawPlane(Shader shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection, unsigned int VAO, GLenum drawMode = GL_TRIANGLES, unsigned int vertecies = 6)
{
	shader.use();
	glBindVertexArray(VAO);

	shader.setMat4("model", model);
	shader.setMat4("view", view);
	shader.setMat4("projection", projection);

	glDrawArrays(drawMode, 0, vertecies);

	glBindVertexArray(0);
}

/// <summary>
/// Draws the plane that will be used for the shadow mapping process
/// </summary>
/// <param name="shader">Shader that shadow maps use</param>
/// <param name="model">Model matrix where to locate it in world space</param>
/// <param name="lightSpaceMatrix">Transfrom points in the light's POV</param>
/// <param name="VAO">Vertex array object to use</param>
void DrawShadowMapPlane(Shader shader, glm::mat4 model, unsigned int VAO)
{
	shader.use();
	glBindVertexArray(VAO);

	shader.setMat4("model", model);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
}

/// <summary>
/// Draws a sphere with instanced approach
/// </summary>
/// <param name="shader">Shader to use for rendering</param>
/// <param name="view">View matrix to transform to view space</param>
/// <param name="projection">Projection matrix to trasform to clip space</param>
/// <param name="VAO">Vertex array object to render</param>
/// <param name="indexNum">Number of inecies</param>
/// <param name="instanceCount">Number of instance we are goign to render</param>
void DrawSphereInstanced(Shader shader, glm::mat4 view, glm::mat4 projection, unsigned int VAO, int indexNum, int instanceCount)
{
	setMatrices(shader, glm::mat4(1.0), view, projection);
	glBindVertexArray(VAO);
	glDrawElementsInstanced(GL_TRIANGLE_STRIP, indexNum, GL_UNSIGNED_INT, 0, instanceCount);
	glDisable(GL_CULL_FACE);
}

void DrawSphere(Shader shader, glm::mat4 model, glm::mat4 view, glm::mat4 projection, unsigned int VAO, int indexNum)
{
	setMatrices(shader, model, view, projection);
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLE_STRIP, indexNum, GL_UNSIGNED_INT, 0);
	glDisable(GL_CULL_FACE);
}
