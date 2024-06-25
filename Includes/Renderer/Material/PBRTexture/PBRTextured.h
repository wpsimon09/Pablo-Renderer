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
#include "imgui.h"
#include "Renderer/Utils/Texture/Texture2D/Texture2DArray.h"
#include "Renderer/Utils/AssetsManager/AssetsManager.h"
#include "PBRTexturedUI.h"
/***
 * Class representing PBR material with textures
 * @inherit Material.h
 */
class PBRTextured : public Material {
public:
    /**
     * Loads material from texture folder
     * @param fileFormat format of the texture file default value is .png
     * @param pathToTheDirectory relative path to the directory with textures
     * @param shaderNamingConvention naming conventions used in the shader for unifrom samplers
     * @param isRelativePath determines if the path is relative to the engine directory
     * false means that textures are located somewhere in the directory of the engine
     * */
    explicit PBRTextured(bool supportsAreaLight = false, std::string pathToTheDirectory = "",
                         bool isRelativePath = true, std::string shaderNamingConvention = "_",
                         std::string fileFormat = ".png");


    std::shared_ptr<Texture2D> getAlbedoTexture() override;

    std::vector<std::reference_wrapper<Texture2D> > getTextures() override;

    /***
     * Passes all information to the shader unifroms
     */
    void configureShader() override;

    /***
     * Adds texture to be used as material property
     * @param texture texture representing material proerty
     */
    void addTexture(std::shared_ptr<PBRMaterial<Texture2D> > texture);

    void renderUI() override;

    bool hasEmissionTexture = false;

private:
    void loadMaterials(AssetsManager *assetsManagerInstance, std::string pathToTheDirectory = "",
                       bool isRelativePaht = true, std::string shaderNamingConvention = "_",
                       std::string fileFormat = ".png");

    std::unique_ptr<Texture2DArray> material;

    /***
     * All the textures the material possess
     */
    std::vector<std::shared_ptr<PBRMaterial<Texture2D> > > textures;
};


#endif //PABLO_RENDERER_PBRTEXTURED_H
