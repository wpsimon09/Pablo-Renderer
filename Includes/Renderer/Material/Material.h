//
// Created by wpsimon09 on 30/12/23.
//

#ifndef CLIONTEST_MATERIAL_H
#define CLIONTEST_MATERIAL_H

#include <utility>

#include "Shader.h"
#include "iostream"
#include "memory"
/***
 * Struct for storing information about material
 * @tparam T property of the material datatype eg.: color, texture, etc...
 */
template<typename T>
struct PBRMaterial {
    std::shared_ptr<T> type;
    std::string shaderName;
    int samplerID;

    /***
     * Create PBR material instance
     * @param type value of the material
     * @param shaderName name that matches the shader's uniform name
     * @param samplerid sampler that is used for the textures
     */
    PBRMaterial(std::shared_ptr<T> type, std::string shaderName, int samplerid = 0) {
        this->type = std::move(type);
        this->shaderName = shaderName;
        this->samplerID = samplerid;
    }

    /***
     * Creates PBR material instance
     * @param type value of the property
     * @param shaderName name that matches the shader's unifrom name
     * @param samplerid sampler that is used for the textures
     */
    PBRMaterial(T type, std::string shaderName, int samplerid = 0) {
        this->type = std::make_unique<T>(std::move(type));
        this->shaderName = shaderName;
        this->samplerID = samplerid;
    }
};

class Material {
public:
    std::shared_ptr<Shader> shader;

    bool supportsIBL;

    Material() = default;

    /***
     * Creates an instance of the material class
     * @param shader
     */
    explicit Material(std::shared_ptr<Shader> shader) {
        this->shader = std::move(shader);
    }

    /***
     * Pass all of the relevant uniforms to the shader
     */
    virtual void configureShader() {};

    /***
     * Unbinds all of the textures bound during rendering
     */
    virtual void unbindTextures(){}

    ~Material() = default;

    virtual void printLog() const {};
protected:
    /***
     * Number of samplers that are used in the given material
     */
    int samplerCount = 0;
public:
    int getSamplerCount() const { return samplerCount; }
};


#endif //CLIONTEST_MATERIAL_H
