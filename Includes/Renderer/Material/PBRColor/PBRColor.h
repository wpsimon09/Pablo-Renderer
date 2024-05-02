//
// Created by wpsimon09 on 31/12/23.
//

#ifndef PABLO_RENDERER_PBRCOLOR_H
#define PABLO_RENDERER_PBRCOLOR_H

#include "Renderer/Material/Material.h"
#include "memory"
#include "imgui.h"

/***
 * Class representing material that has no textures apply to it
 */
class PBRColor: public Material {
public:
    /***
     * Creates an instance of the class
     * @param shader shader that is used by the object
     * @param albedo base color (rgb)
     * @param metallic metallic value
     * @param rougness roughness value
     * @param ao ambient occulsion value
     * @param shaderNamingConvention naming convention of the shader defualt is _val eg: _valAlbedo, _valMetallic
     */
    explicit PBRColor(glm::vec3 albedo = glm::vec3(0.4f, 0.4f, 0.4f),bool supportsIBL = false,bool supportsAreaLight = false, float metallic = 0.7f , float rougness = 0.2f, float ao= 0.6f, std::string shaderNamingConvention = "_val");
private:
    std::unique_ptr<PBRMaterial<glm::vec3>> albedo;
    std::unique_ptr<PBRMaterial<float>> metalness;
    std::unique_ptr<PBRMaterial<float>> rougness ;
    std::unique_ptr<PBRMaterial<float>> ao;
public:
    void renderUI() override;

public:
    friend std::ostream& operator<<(std::ostream& os, const PBRColor& mat);

    void printLog() const override;

    /***
     * Sets all of the information to the shader uniforms using the naming convention specified in contractor
     */
    void configureShader() override;
};


#endif //PABLO_RENDERER_PBRCOLOR_H
