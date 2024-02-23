//
// Created by wpsimon09 on 06/01/24.
//

#include "Light.h"
#include "Renderer/Geometry/Shapes/ScreenSpaceQuad/ScreenSpaceQuadGeometry.h"
#include "Renderer/Material/Material.h"
#include "Renderer/Material/BasicMaterialTexturd/BasicMaterialTextured.h"

Light::Light(glm::vec3 position, glm::vec3 color) {
    this->position = std::make_unique<LightProperty<glm::vec3>>(position, "lightPositions[0]");
    this->color = std::make_unique<LightProperty<glm::vec3>>(color, "lightColors[0]");

    std::unique_ptr<Geometry> geometry = std::make_unique<ScreenSpaceQuadGeometry>();
    std::unique_ptr<Material> material = std::make_unique<BasicMaterialTextured>(std::make_shared<Shader>("VertexShader/AdvancedLightning/LightSourceVertex.glsl", "FragmentShader/AdvancedLightning/LightSourceFragment.glsl", "light sourece"), "Assets/Textures/AdvancedLightning/sun.png", "lightTexture");
    material->shader->use();
    material->shader->setVec3("lightColor", this->color->property);
    std::unique_ptr<Renderable> lightRenderable = std::make_unique<Renderable>(std::move(geometry), std::move(material));
    this->lightSceneNode = std::make_shared<SceneNode>(std::move(lightRenderable));
    this->lightSceneNode->setScale(glm::vec3(0.2));
    this->lightSceneNode->setPositions(this->position->property);
}

void Light::update(std::shared_ptr<Shader> shader) {
    shader->use();
    shader->setVec3(this->position->uniformName, this->position->property);
    shader->setVec3(this->color->uniformName, this->color->property);

    this->lightSceneNode->setPositions(this->position->property);
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

void Light::render() {
    this->lightSceneNode->render();
}
