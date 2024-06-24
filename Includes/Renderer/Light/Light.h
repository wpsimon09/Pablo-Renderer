//
// Created by wpsimon09 on 06/01/24.
//

#ifndef PABLO_RENDERER_LIGHT_H
#define PABLO_RENDERER_LIGHT_H

#include "iostream"
#include "glm/glm.hpp"
#include "Shader.h"
#include "Renderer/SceneGraph/SceneNode/SceneNode.h"
#include "imgui.h"
#include "Renderer/Utils/ShaderManager/ShaderManager.h"
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

    /***
     * Updates the shader that contains the light
     * @param shader shader in which the light should be updated
     * @param isCastingShadows is object which is processing light casting shadow @def false
     */
    virtual void update(std::shared_ptr<Shader> shader, bool isCastingShadows = false){};

    /***
     * Renders the light icon in the currently bound frame buffer
     */
    virtual void render(glm::mat4 viewMatrix, glm::mat4 projectionMatrix){};

    /***
     * Renders the UI for the light properties
     */
    virtual void renderUi();

    /**
     * @brief Prepares the Light for the next frame
     */
    void prepareForNextFrame();

    /**
     * @brief Returns updated sampler value if area light is applied as it is using LTC texture
     */
    unsigned int getUpdatedSampler() {return this->currentSampler;}


    /**
     * @brief Sets the sampler that will be used for LTC textures
     * @param sampler sampler to be used
     */
    void setCurrentSampler(int sampler) {this->currentSampler = sampler;}

     /***
     * Renderer which purpose is to visualize light position in the world
     */
    std::shared_ptr<Renderable> lightRenderable;

    /**
     * @brief Near plane of the light used for shadow mapping
     */
    float lightNearPlane = 1.0f;

    /**
     * @brief Far plane of the light used for shadow mapping
     */
    float lightFarPlane = 20.0f;

protected:
    /**
     * @brief Sampler to be used for binding LTC texture
     */
    unsigned int currentSampler;

    void createLightMatrices();

    /***
     * Updates shader responsible for showing light on scene
     */
    void updateInternal();

    /**
     * @brief Updates light view matrix of the light for shadow calculations
     */
    virtual void updateLightViewMatrix();

    /**
     * @brief Calculates final colour of the light
     * @return Colour of the light multyplied by brightness
     */
    glm::vec3 calculateFinalLightColor(){return (this->color->property * lightStrength);}

    /**
     * @brief Typeof the ligh
     */
    std::string type;

    const float lightSpeed = 0.05f;
    float lightStrength = 1.0f;

    std::unique_ptr<LightProperty<glm::mat4>> lightViewMatrix;
    std::unique_ptr<LightProperty<glm::mat4>> lightProjectionMatrix;
    std::unique_ptr<LightProperty<glm::mat4>> lightModelMatrix;
    std::unique_ptr<LightProperty<glm::vec3>> position;
    std::unique_ptr<LightProperty<glm::vec3>> color;


};


#endif //PABLO_RENDERER_LIGHT_H
