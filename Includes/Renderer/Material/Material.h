//
// Created by wpsimon09 on 30/12/23.
//

#ifndef CLIONTEST_MATERIAL_H
#define CLIONTEST_MATERIAL_H

#include <utility>

#include "Shader.h"
#include "iostream"
#include "memory"
#include "Renderer/Utils/Texture/Texture2D/Texture2D.h"
#include "Renderer/Utils/ShaderManager/ShaderManager.h"

class MaterialID {
public:
 static inline float id = 0;
};

/***
 * Struct for storing information about material
 * @tparam T property of the material datatype eg.: color, texture, etc...
 */
template<typename T>
struct PBRMaterial {
    std::shared_ptr<T> type;
    std::string shaderName;
    int samplerID;
    MATERIAL_TEXTURE_TYPE material_type;

    /***
     * Create PBR material instance
     * @param type value of the material
     * @param shaderName name that matches the shader's uniform name
     * @param samplerid sampler that is used for the textures
     */
    PBRMaterial(std::shared_ptr<T> type, std::string shaderName, int samplerid = 0, MATERIAL_TEXTURE_TYPE texture_type = UNDEFINED) {
        this->type = type;
        this->shaderName = shaderName;
        this->samplerID = samplerid;
        this->material_type = texture_type;
    }

    /***
     * Creates PBR material instance
     * @param type value of the property
     * @param shaderName name that matches the shader's unifrom name
     * @param samplerid sampler that is used for the textures
     */
    PBRMaterial(T type, std::string shaderName, int samplerid = 0,MATERIAL_TEXTURE_TYPE texture_type = UNDEFINED) {
     this->type = std::make_shared<T>(type);
     this->shaderName = shaderName;
     this->samplerID = samplerid;
     this->material_type = texture_type;
    }
};

class Material {
public:
    Material() { this-> ID = MaterialID::id++;}

    /***
     * Creates an instance of the material class
     * @param shader
     */
    explicit Material(std::shared_ptr<Shader> shader) {
        this->shader = std::move(shader);
        this->ID =  MaterialID::id++;
    }

    ~Material()= default;

    unsigned int getID() const{return this->ID;}

    /***
     * Pass all of the relevant uniforms to the shader
     */
    virtual void configureShader() {
    };

    /***
     * @brief Gets all of the of textures if material has any (virutal)
     * @return vector of shared pointer to the textures
     */
    virtual std::vector<std::reference_wrapper<Texture2D> > getTextures() {
        std::vector<std::reference_wrapper<Texture2D> > tex;
        return tex;
    };

    /***
     * Unbinds all of the textures bound during rendering
     */
    virtual void unbindTextures() {
    }

    /**
     * @brief Renders UI of the concrete material
     * @note this method is overwritten in concrete materials
     */
    virtual void renderUI() {
    };

    /**
     * @brief Gets albedo texture of the material
     * @return albedo texture of the material or nullptr if no texture is found
     */
    virtual std::shared_ptr<Texture2D> getAlbedoTexture() { return nullptr; };

    /**
     * @brief Gets the albedo colour of the matreial if found otherwise trhrows exception
     * @return RGB represenation of the albedo material
     */
    virtual glm::vec3 getAlbedoColour() {return glm::vec3(-1.0f);}

    /**
     * @brief Prints log
     * @deprecated This does not work anymore
     */
    virtual void printLog() const {
    };

    std::string getName() {return this->name;}

    std::shared_ptr<Shader> shader;

    bool supportsIBL = false;
    bool supportsAreaLight = false;

protected:
    /***
     * Number of samplers that are used in the given material
     */
    int samplerCount = 0;

    /**
     * @brief Unique identifier of the material
     */
    unsigned int ID = 0;

    std::string name;
public:
    int getSamplerCount() const { return samplerCount; }

    bool operator == (const Material  &other) const;
};


#endif //CLIONTEST_MATERIAL_H
