//
// Created by wpsimon09 on 06/01/24.
//

#include "Light.h"
#include "Renderer/Geometry/Shapes/ScreenSpaceQuad/ScreenSpaceQuadGeometry.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Material/BasicMaterialTexturd/BasicMaterialTextured.h"

Light::Light(glm::vec3 position, glm::vec3 color) {
    this->position = new LightProperty(position, "lightPositions[0]");
    this->color = new LightProperty(color, "lightColors[0]");

    Geometry *geometry = new ScreenSpaceQuadGeometry();
    Material *material = new BasicMaterialTextured(new Shader("VertexShader/AdvancedLightning/LightSourceVertex.glsl", "FragmentShader/AdvancedLightning/LightSourceFragment.glsl", "light sourece"), "Assets/Textures/AdvancedLightning/sun.png");
    material->shader->use();
    material->shader->setVec3("lightColor", this->color->property);
    Renderable *lightTexutre = new Renderable(geometry, material);
    this->lightIcon = new SceneNode(lightTexutre);
    this->lightIcon->setPositions(this->position->property);
}

void Light::update(Shader *shader) {
    shader->use();
    shader->setVec3(this->position->uniformName, this->position->property);
    shader->setVec3(this->color->uniformName, this->color->property);

    this->lightIcon->setPositions(this->position->property);
    this->lightIcon->setScale(glm::vec3(0.2));
}

void Light::setX(float pos) {
    this->position->property.x = pos;
}

void Light::setY(float pos) {
    this->position->property.y = pos;
}

void Light::setZ(float pos) {
    this->position->property.z= pos;
}

void Light::processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        this->position->property.z += lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        this->position->property.z -= lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        this->position->property.x += lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        this->position->property.x -= lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        this->position->property.y -= lightSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        this->position->property.y += lightSpeed;
}
