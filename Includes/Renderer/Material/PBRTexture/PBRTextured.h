//
// Created by wpsimon09 on 31/12/23.
//

#ifndef PABLO_RENDERER_PBRTEXTURED_H
#define PABLO_RENDERER_PBRTEXTURED_H

#include "Renderer/Material/Material.h"
#include "Renderer/Utils/Texture/Texture2D/Texture2D.h"
#include "iostream"
#include "vector"
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
    explicit PBRTextured(std::unique_ptr<Shader> shader, std::string pathToTheDirectory,  std::string shaderNamingConvention = "_", std::string fileFormat = ".png");

    explicit PBRTextured(std::unique_ptr<Shader> shader);

    void configureShader() override;

    void addTexture(std::unique_ptr<PBRMaterial<Texture2D> > texture);

    void clearAddedTextures();

    ~PBRTextured()= default;

private:
    std::vector<std::unique_ptr<PBRMaterial<Texture2D>>> textures;
};


#endif //PABLO_RENDERER_PBRTEXTURED_H
