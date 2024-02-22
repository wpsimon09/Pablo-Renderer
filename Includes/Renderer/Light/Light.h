//
// Created by wpsimon09 on 06/01/24.
//

#ifndef PABLO_RENDERER_LIGHT_H
#define PABLO_RENDERER_LIGHT_H

#include "iostream"
#include "glm/glm.hpp"
#include "Shader.h"
#include "Renderer/SceneGraph/SceneNode/SceneNode.h"
template<typename T>
struct LightProperty{
    T property;
    std::string uniformName;
    LightProperty(T property, std::string unifrom){
        this->property = property;
        this->uniformName = unifrom;
    }
};

class Light {
public:
    Light(glm::vec3 position, glm::vec3 color);

    void setX(float pos);
    void setY(float pos);
    void setZ(float pos);

    void processInput(GLFWwindow* window);

    /**
     * Lets updates the shader abut the current light position
     * */
    virtual void update(std::shared_ptr<Shader> shader);

    virtual void render();
    std::shared_ptr<SceneNode> lightSceneNode;

protected:

    const float lightSpeed = 0.05f;
    std::unique_ptr<LightProperty<glm::vec3>> position;
    std::unique_ptr<LightProperty<glm::vec3>> color;
};


#endif //PABLO_RENDERER_LIGHT_H
