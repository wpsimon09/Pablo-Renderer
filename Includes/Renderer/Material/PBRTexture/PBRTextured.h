//
// Created by wpsimon09 on 31/12/23.
//

#ifndef PABLO_RENDERER_PBRTEXTURED_H
#define PABLO_RENDERER_PBRTEXTURED_H

#include "Renderer/Material/Material.h"
#include "Renderer/Utils/Texture/Texture2D.h"
#include "iostream"
#include "ostream"
class PBRTextured : public Material{
public:
    // ASSUMPTION WARNING
    // assumption here is made that within the directory materials follow the following naming convention
    // the path parameter should be passed as
    // Assets/Textures/directory
    // albedo.png/jpg, metallic.png/jpg, rougness.png/jpg

    /**
     * Loads material from texture folder
     * @param fileFormat format of the texture file default value is .png
     * @param pathToTheDirectory relative path to the directory with textures
     * @param shader shader that will be assosiated with texture
     * @param shaderNamingConvention naming conventions used in the shader for unifrom samplers
     * */
    explicit PBRTextured(Shader* shader, std::string pathToTheDirectory,  std::string shaderNamingConvention = "_", std::string fileFormat = ".png");

    explicit PBRTextured(Shader* shader, PBRMaterial<Texture2D>* baseColor, PBRMaterial<Texture2D>* normalMap, PBRMaterial<Texture2D>* emmisionMap = nullptr, PBRMaterial<Texture2D>* metalnessRougnessMap = nullptr, PBRMaterial<Texture2D>* rougness = nullptr, PBRMaterial<Texture2D>* metalness = nullptr, PBRMaterial<Texture2D>* ao = nullptr);

    friend std::ostream& operator<<(std::ostream& os, const PBRTextured& mat);

    void printLog() const override;

    void configureShader() override;

private:
    PBRMaterial<Texture2D>* baseColor = nullptr;
    PBRMaterial<Texture2D>* normalMap = nullptr;
    PBRMaterial<Texture2D>* roughness = nullptr;
    PBRMaterial<Texture2D>* metalness = nullptr;
    PBRMaterial<Texture2D>* ao = nullptr;
    PBRMaterial<Texture2D>* emmisionMap = nullptr;
    PBRMaterial<Texture2D>* metallnesRougnessMap = nullptr;
};


#endif //PABLO_RENDERER_PBRTEXTURED_H
