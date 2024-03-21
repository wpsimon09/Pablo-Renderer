//
// Created by wpsimon09 on 06/01/24.
//

#ifndef PABLO_RENDERER_LIGHT_H
#define PABLO_RENDERER_LIGHT_H

#include "iostream"
#include "glm/glm.hpp"
#include "Shader.h"
#include "Renderer/SceneGraph/SceneNode/SceneNode.h"

/***
 * Struct representing light property
 * @tparam T type of the property vec3, int , float, etc...
 */
template<typename T>
struct LightProperty{
    T property;
    std::string uniformName;
    /***
     * Creates an instance of the LightProperty struct
     * @param property value of the property
     * @param unifrom uniform to be used within shader
     */
    LightProperty(T property, std::string unifrom){
        this->property = property;
        this->uniformName = unifrom;
    }
};

class Light {
public:
    /***
     * Creates an instance of the light
     * @param position position of the light in the world space
     * @param color color of the light
     */
    Light(glm::vec3 position, glm::vec3 color);

    void setX(float pos);
    void setY(float pos);
    void setZ(float pos);

    /***
     * Process input for the light
     * @param window window in which to check the input in
     */
    void processInput(GLFWwindow* window);

    /***
     * Updates the shader that contains the light
     * @param shader shader in which the light should be updated
     */
    virtual void update(std::shared_ptr<Shader> shader);

    /***
     * Renders the light icon in the currently bound frame buffer
     */
    virtual void render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

    /***
     * Renderer which purpose is to visualize light position in the world
     */
    std::shared_ptr<Renderable> lightRenderable;

protected:

    const float lightSpeed = 0.05f;
    std::unique_ptr<LightProperty<glm::vec3>> position;
    std::unique_ptr<LightProperty<glm::vec3>> color;
};


#endif //PABLO_RENDERER_LIGHT_H
