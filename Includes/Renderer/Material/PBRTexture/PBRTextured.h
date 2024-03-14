//
// Created by wpsimon09 on 31/12/23.
//

#ifndef PABLO_RENDERER_PBRTEXTURED_H
#define PABLO_RENDERER_PBRTEXTURED_H

#include "Renderer/Material/Material.h"
#include "Renderer/Utils/Texture/Texture2D/Texture2D.h"
#include "Renderer/Utils/Texture/TextureBase.h"
#include "iostream"
#include "vector"
#include "ostream"
#include "Renderer/Utils/ShaderHelper/ShaderHelper.h"

/***
 * Class representing PBR material with textures
 * @inherit Material.h
 */
class PBRTextured : public Material{
public:
    /**
     * Loads material from texture folder
     * @param fileFormat format of the texture file default value is .png
     * @param pathToTheDirectory relative path to the directory with textures
     * @param shader shader that will be assosiated with texture
     * @param shaderNamingConvention naming conventions used in the shader for unifrom samplers
     * */
    explicit PBRTextured(std::shared_ptr<Shader> shader, std::string pathToTheDirectory,  std::string shaderNamingConvention = "_", std::string fileFormat = ".png");

    /***
     * Creates empty instance of the class
     * @param shader shader the material should use
     */
    explicit PBRTextured(std::shared_ptr<Shader> shader);

    /***
     * Passes all information to the shader unifroms
     */
    void configureShader() override;

    /***
     * Adds texture to be used as material property
     * @param texture texture representing material proerty
     */
    void addTexture(std::unique_ptr<PBRMaterial<Texture2D>> texture);

    ~PBRTextured()= default;

private:
    /***
     * All the textures the material possess
     */
    std::vector<std::unique_ptr<PBRMaterial<Texture2D>>> textures;
};


#endif //PABLO_RENDERER_PBRTEXTURED_H
